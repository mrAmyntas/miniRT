#include "../inc/miniRT.h"

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
	tmp = normalize_vector(subtract_vectors(scene->light[scene->i].ori, Phit));
	t = dot_product(*N, tmp);
	angle = acos(t) / (M_PI / 180);
	return (angle);
}

// calculates the angle light hits Phit on a cylinder
double	get_cy_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		angle;
	double		t;
	t_vect3d	tmp;

	if (scene->cy[num[1]].cap > 0)
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

static void	calc_t_val(t_scene *scene, t_ray *ray, t_vect3d *tmp, double *t)
{
	t[0] = (dot_product(scene->ori_dir, tmp[0]))
			/ (dot_product(scene->ori_dir, ray->dir));
	t[1] = (dot_product(scene->ori_dir, tmp[1]))
			/ (dot_product(scene->ori_dir, ray->dir));
}

//calculates if ray hits the cap (basically a disc)
//this would be missed if ray doesnt hit sides within
//valid z ranges
double	find_caps(t_scene *scene, int *num, t_ray *ray, int cap)
{
	t_vect3d	tmp[2];
	double		t[2];
	t_vect3d	P;

	P = scene->origin;
	if (dot_product(scene->ori_dir, ray->dir) == 0)
		return (-1);
	tmp[0] = subtract_vectors(P, ray->eye);
	P.z = scene->cy[*num].height;
	tmp[1] = subtract_vectors(P, ray->eye);
	t[0] = (dot_product(scene->ori_dir, tmp[0]))
			/ (dot_product(scene->ori_dir, ray->dir));
	t[1] = (dot_product(scene->ori_dir, tmp[1]))
			/ (dot_product(scene->ori_dir, ray->dir));
	tmp[0] = add_vectors(ray->eye, multiply_vector(ray->dir, t[0]));
	tmp[0] = subtract_vectors(tmp[0], scene->ori_dir);
	tmp[1] = add_vectors(ray->eye, multiply_vector(ray->dir, t[1]));
	tmp[1] = subtract_vectors(tmp[1], scene->ori_dir);
	if (t[0] > 0 && dot_product(tmp[0], tmp[0]) <= (scene->cy[*num].r * scene->cy[*num].r)
		&& (t[1] < 0 || (dot_product(tmp[1], tmp[1]) > (scene->cy[*num].r * scene->cy[*num].r))))
	{
		if (cap == 1)
			scene->cy[*num].cap = TOP;
		return (t[0]);
	}
	else if (t[1] > 0 && dot_product(tmp[1], tmp[1]) <= (scene->cy[*num].r * scene->cy[*num].r))
	{
		if (cap == 1)
			scene->cy[*num].cap = BOT;
		return (t[1]);
	}
	scene->cy[*num].cap = NOT;
	return (-1);
}

double	find_closest_cy(t_scene *scene, t_ray *ray, int *num, int cap)
{
	t_cy_data	cy;
	t_vect3d	P;

	P = scene->origin;
	transform_ray(scene, ray, num, cy.z_m);
	cy.ret = calc_t_0_1(scene, ray, num, cy.t);
	if (isnan(cy.t[0])  && isnan(cy.t[1]))
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
	*num = find_smallest(scene, t, *num, scene->amount[CYLINDER]);
	if (*num == -1)
	{
		free (t);
		return (-1);
	}
	ret = t[*num];
	free (t);
	return (ret);
}
