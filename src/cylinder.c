#include "../inc/miniRT.h"

static double	get_cy_angle_side(t_scene *scene, int num[2],
		t_vect3d Phit, t_vect3d *N)
{
	double		t;
	double		angle;
	t_vect3d	tmp;

	t = magnitude(subtract_vectors(Phit, scene->cy[num[1]].eye));
	t = fabs((t * t) - (scene->cy[num[1]].r * scene->cy[num[1]].r));
	t = sqrt(t);
	tmp = add_vectors(scene->cy[num[1]].eye,
			multiply_vector(scene->cy[num[1]].dir, t));
	*N = normalize_vector(subtract_vectors(Phit, tmp));
	tmp = normalize_vector(subtract_vectors(scene->light[scene->i].ori, Phit));
	t = dot_product(*N, tmp);
	angle = acos(t) / (M_PI / 180);
	return (angle);
}

// calculates the angle light hits Phit on a cylinder
double	get_cy_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		angle;
	t_vect3d	tmp;

	if (scene->cy[num[1]].cap != NOT)
	{
		if (scene->cy[num[1]].cap == BOT)
			*N = multiply_vector(scene->cy[num[1]].dir, -1);
		else
			*N = scene->cy[num[1]].dir;
		tmp = normalize_vector(subtract_vectors(
					scene->light[scene->i].ori, Phit));
		angle = acos(dot_product(*N, tmp)) / (M_PI / 180);
	}
	else
		angle = get_cy_angle_side(scene, num, Phit, N);
	return (angle);
}

//translation and rotation of ray and set z-min and z-max.
//the cylinder intersect points are calculated as if it's 
//origin is in the world origin, aligned along the z-axis
//so the ray which comes from the camera in world space
//needs to be translated and rotated with the inverse of
//the translation and rotation that the cylinder has compared
//to its origin position.
//z_m[0] is z_min is 0, z_m[1] is z_max is the height
double	find_closest_cy(t_scene *scene, t_ray *ray, int *num, int cap)
{
	t_cy_data	cy;

	cy.z_m[0] = 0;
	cy.z_m[1] = scene->cy[*num].height;
	translate_ray(&ray->eye, scene->cy[*num].i_t);
	rotate_ray(ray, scene->cy[*num].i_r);
	cy.ret = calc_t_0_1(scene, ray, num, cy.t);
	if (isnan(cy.t[0]) && isnan(cy.t[1]))
		return (find_caps(scene, num, ray, cap));
	cy.z[0] = ray->eye.z + ray->dir.z * cy.t[0];
	cy.z[1] = ray->eye.z + ray->dir.z * cy.t[1];
	if (t_closest(cy.t[0], cy.t[1], cy.z_m, cy.z[0]))
		return (find_intersect(ray, cy, &scene->cy[*num].cap, cap));
	else if (t_closest(cy.t[1], cy.t[0], cy.z_m, cy.z[1]))
	{
		cy.t[0] = cy.t[1];
		return (find_intersect(ray, cy, &scene->cy[*num].cap, cap));
	}
	else
		return (find_caps(scene, num, ray, cap));
}

double	find_hit_cy(t_scene *scene, t_ray *ray, int *num, int cap)
{
	double	*t;
	t_ray	new_ray;
	double	ret;

	t = malloc(sizeof(double) * scene->amount[CYLINDER]);
	*num = 0;
	while (*num < scene->amount[CYLINDER])
	{
		new_ray = *ray;
		t[*num] = find_closest_cy(scene, &new_ray, num, cap);
		*num = *num + 1;
	}
	*num = find_smallest(t, *num, scene->amount[CYLINDER]);
	if (*num == -1)
	{
		free (t);
		return (-1);
	}
	ret = t[*num];
	free (t);
	return (ret);
}
