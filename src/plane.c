#include "../inc/miniRT.h"

int	check_if_plane_between_cam_and_light(t_scene *scene, t_vect3d Phit[2])
{
	t_ray	ray;
	int		num2;
	int		num3;
	double	t2[2];

	ray.eye = scene->light->ori;
	ray.dir = normalize_vector(subtract_vectors(Phit[0], ray.eye));
	t2[0] = find_hit_pl(scene, &ray, &num2, 0);
	ray.eye = scene->cam->eye;
	ray.dir = normalize_vector(subtract_vectors(scene->light->ori, ray.eye));
	t2[1] = find_hit_pl(scene, &ray, &num3, 0);
	if (t2[1] > 0 && num2 == num3 && t2[1]
		< distance_two_points(scene->cam->eye, scene->light->ori))
		return (0);
	return (1);
}

// calculates the angle light hits Phit on a plane
double	get_pl_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		angle;
	t_vect3d	tmp;

	tmp = normalize_vector(subtract_vectors(scene->light[scene->i].ori, Phit));
	angle = acos(dot_product(scene->pl[num[1]].orth_vec, tmp)) / (M_PI / 180);
	*N = scene->pl[num[1]].orth_vec;
	if (angle > 90)
	{
		angle = 180 - angle;
		*N = multiply_vector(*N, -1);
	}
	return (angle);
}

//finds smallest non-negative t-value and returns which t_value this is
//if none, returns -1
int	find_smallest(double *t, int num, int amount)
{
	int	i;
	int	j;

	if (num == 0)
		return (-1);
	i = 0;
	j = 1;
	while (i + j < amount)
	{
		if (t[i + j] > 0 && (t[i + j] < t[i] || t[i] < 0))
		{
			i = i + j;
			j = 1;
		}
		else
			j++;
	}
	if (t[i] > 0)
		return (i);
	return (-1);
}

//calculates t_value for each plane
//73: checks if plane/ray are parallel
static void	calc_t(t_scene *scene, t_ray *ray, int *num, double *t)
{
	t_vect3d	tmp;

	*num = 0;
	while (*num < scene->amount[PLANE])
	{
		tmp = subtract_vectors(scene->pl[*num].coord, ray->eye);
		if (dot_product(scene->pl[*num].orth_vec, ray->dir) == 0)
		{
			t[*num] = -1;
			*num = *num + 1;
			continue ;
		}
		t[*num] = (dot_product(scene->pl[*num].orth_vec, tmp))
			/ (dot_product(scene->pl[*num].orth_vec, ray->dir));
		*num = *num + 1;
	}
}

//check if the camera ray will hit with the plane[num]
//num is set to closest planes num, distance is returned.
double	find_hit_pl(t_scene *scene, t_ray *ray, int *num, int set)
{
	double		*t;
	double		ret;
	t_vect3d	phit;

	t = malloc(sizeof(double) * scene->amount[PLANE]);
	calc_t(scene, ray, num, t);
	*num = find_smallest(t, *num, scene->amount[PLANE]);
	if (*num != -1)
	{
		ret = t[*num];
		free (t);
		if (scene->cb[ON] == true && set == 1)
		{
			phit = add_vectors(scene->ray_cam.eye,
					multiply_vector(scene->ray_cam.dir, ret));
			scene->pl[*num].checker = checkerboard_pl(scene, phit, *num);
		}
		return (ret);
	}
	free (t);
	return (-1);
}

void	set_axis(t_vect3d *axis, t_scene *scene, int num)
{
	t_vect3d	a;
	t_vect3d	b;
	t_vect3d	l;

	a = scene->pl[num].orth_vec;
	b = a;
	if (comp_d(b.x, 0.0))
		b.x = b.x + 0.1;
	else if (comp_d(b.y, 0.0))
		b.y = b.y + 0.1;
	else if (comp_d(b.z, 0.0))
		b.z = b.z + 0.1;
	else
		b.x = b.x + 1;
	axis[0] = normalize_vector(cross_product(a, b));
	axis[1] = normalize_vector(cross_product(axis[0], a));
}

void	find_angles(double *angle, t_vect3d l, t_vect3d *axis)
{
	angle[0] = acos(dot_product(l, axis[0]) / magnitude(l));
	angle[1] = acos(dot_product(l, axis[1]) / magnitude(l));
}

//u len 0
// v len 1
int	find_lenghts(t_vect3d l, t_vect3d *axis, double *angle, double *len)
{
	int	c;

	c = 0;
	if (angle[0] > 1.5707963268)
	{
		axis[0] = multiply_vector(axis[0], -1);
		angle[0] = acos(dot_product(l, axis[0]) / magnitude(l));
		c = 1;
	}
	if (angle[1] < 1.5707963268)
		c = c + 2;
	len[0] = cos(angle[0]) * magnitude(l);
	len[1] = sin(angle[0]) * magnitude(l);
	if (c == 0 || c == 3)
		return (1);
	return (0);
}

//checks which color pattern the current Phit has
//either returns 1 or 0
//the distances in 2 perpendicular directions are calculated
//both those directions are also perpendicular to the plane 
//vector, so it is like a 3d axis system.
//Based on the distance the point is in these 2 directions
//relative to the original plane coordinates,
//it is either part of a normal or reversed color pattern.
int	checkerboard_pl(t_scene *scene, t_vect3d Phit, int num)
{
	t_vect3d	l;
	t_vect3d	axis[2];
	double		angle[2];
	double		len[2];

	len[0] = 0;
	len[1] = 0;
	set_axis(axis, scene, num);
	l = subtract_vectors(Phit, scene->pl[num].coord);
	find_angles(angle, l, axis);
	if (find_lenghts(l, axis, angle, len) == 1)
	{
		if ((((int)(len[0] / scene->cb[H]) % 2) && ((int)(len[1] / scene->cb[W])
			% 2)) || (!((int)(len[0] / scene->cb[H]) % 2) && !((int)(len[1]
			/ scene->cb[W]) % 2)))
			return (0);
		return (1);
	}
	if ((((int)(len[0] / scene->cb[H]) % 2) && ((int)(len[1] / scene->cb[W])
		% 2)) || (!((int)(len[0] / scene->cb[H]) % 2) && !((int)(len[1]
			/ scene->cb[W]) % 2)))
		return (1);
	return (0);
}

	// if (comp_d(angle[0], 0.0))
	// {
	// 	u = magnitude(l);
	// 	v = 0;
	// }
	// else if (comp_d(angle[0], 1.5707963268))
	// {
	// 	u = 0;
	// 	v = magnitude(l);
	// }
	// else
	// {
	// 	if (angle[0] > 1.5707963268)
	// 	{
	// 		axis[0] = multiply_vector(axis[0], -1);
	// 		angle[0] = acos(dot_product(l, axis[0]) / magnitude(l));
	// 		c = 1;
	// 	}
	// 	if (angle[1] < 1.5707963268)
	// 	{
	// 		if (c == 1)
	// 			c = 0;
	// 		else
	// 			c = 1;
	// 	}
	// 	u = cos(angle[0]) * magnitude(l);
	// 	v = sin(angle[0]) * magnitude(l);
	// }


	// if (comp_d(angle[0], 0.0))
	// 	len[0] = magnitude(l);
	// else if (comp_d(angle[0], 1.5707963268))
	// 	len[1] = magnitude(l);
	// else
