#include "../inc/miniRT.h"


static double	get_cy_angle_side(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		t;
	double		angle;
	t_vect3d	tmp;

	t = magnitude(subtract_vectors(Phit, scene->cy[num[1]].eye));
	t = fabs((t * t) - (scene->cy[num[1]].r * scene->cy[num[1]].r));
	t = sqrt(t);
	tmp.x = scene->cy[num[1]].dir.x * -1;
	tmp.y = scene->cy[num[1]].dir.y * -1;
	tmp.z = scene->cy[num[1]].dir.z;
   	tmp = add_vectors(scene->cy[num[1]].eye, multiply_vector(tmp, t));
   	*N = normalize_vector(subtract_vectors(Phit, tmp));
	tmp = normalize_vector(subtract_vectors(scene->light->ori, Phit));
	t = dot_product(*N, tmp);
	angle = acos(t) / (M_PI / 180);
	if (angle > 90)
		angle = 90;
	return (angle);
}

// calculates the angle light hits Phit on a cylinder
double	get_cy_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		angle;
	double		t;
	t_vect3d	tmp;

	if (scene->cy[num[1]].cap == 1)
	{
		tmp = normalize_vector(subtract_vectors(scene->light->ori, Phit));
		angle = acos(dot_product(scene->cy[num[1]].dir, tmp)) / (M_PI / 180);
		*N = scene->cy[num[1]].dir;
		if (angle > 90)
		{
			angle = 180 - angle;
			*N = multiply_vector(*N, -1);
		}
	}
	else
		angle = get_cy_angle_side(scene, num, Phit, N);
	return (angle);
}

double	find_closest_cy(t_scene *scene, t_ray *ray, int *num, int cap)
{
	t_cy_data	cy;

	transform_ray(scene, ray, num, cy.z_m);
	cy.ret = calc_t_0_1(scene, ray, num, cy.t);
	if (cy.ret == -1)
		return (-1);
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
		return (find_intersect_cap(ray, cy, &scene->cy[*num].cap, cap));
}

double	find_hit_cy(t_scene *scene, t_ray *ray, int *num, int cap)
{
	double	*t;
	t_ray	new_ray;
	double	ret;

	t = malloc(sizeof(double) * scene->amount[2]);
	*num = 0;
	while (*num < scene->amount[2])
	{
		new_ray = *ray;
		t[*num] = find_closest_cy(scene, &new_ray, num, cap);
		*num = *num + 1;
	}
	*num = find_smallest(scene, t, num, scene->amount[2]);
	if (*num == -1)
	{
		free (t);
		return (-1);
	}
	ret = t[*num];
	free (t);
	return (ret);
}
