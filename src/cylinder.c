#include "../inc/miniRT.h"

bool	inside_cylinder_i(t_scene *scene, int i)
{
	t_vect3d	cy_end;
	t_vect3d	A;
	t_vect3d	B;
	t_vect3d	P;
	double		R;
	t_vect3d	e;
	t_vect3d	m;

	cy_end = add_vectors(scene->cy[i].eye, multiply_vector(scene->cy[i].dir, scene->cy[i].height));
	A = scene->cy[i].eye;
	B = cy_end;
	P = scene->cam->eye;
	R = scene->cy[i].r;
	e = scene->cy[i].dir;
//	m = cross_product()
	return true;
}

bool	inside_cylinder(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->amount[CYLINDER])
	{
		if (inside_cylinder_i(scene, i))
			return (true);
		i++;
	}
	return (false);
}

static double	get_cy_angle_side(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		t;
	double		angle;
	t_vect3d	tmp;

	t = magnitude(subtract_vectors(Phit, scene->cy[num[1]].eye));
	t = fabs((t * t) - (scene->cy[num[1]].r * scene->cy[num[1]].r));
	t = sqrt(t);
   	tmp = add_vectors(scene->cy[num[1]].eye, multiply_vector(scene->cy[num[1]].dir, t));
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

	t = malloc(sizeof(double) * scene->amount[CYLINDER]);
	*num = 0;
	while (*num < scene->amount[CYLINDER])
	{
		new_ray = *ray;
		t[*num] = find_closest_cy(scene, &new_ray, num, cap);
		*num = *num + 1;
	}
	*num = find_smallest(scene, t, num, scene->amount[CYLINDER]);
	if (*num == -1)
	{
		free (t);
		return (-1);
	}
	ret = t[*num];
	free (t);
	return (ret);
}
