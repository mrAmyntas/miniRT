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
		if (scene->checkerboard[ON] == true && set == 1)
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

int	checkerboard_pl(t_scene *scene, t_vect3d Phit, int num)
{
	t_vect3d	B;
	t_vect3d	A;
	t_vect3d	u2;
	t_vect3d	v2;
	t_vect3d	l;
	double		u;
	double		v;
	double		angle;
	int			c = 0;
	double		angle2;

	A = scene->pl[num].orth_vec;
	B = A;
	if (comp_d(B.x, 0.0))
		B.x = B.x + 0.1;
	else if (comp_d(B.y, 0.0))
		B.y = B.y + 0.1;
	else if (comp_d(B.z, 0.0))
		B.z = B.z + 0.1;
	else
		B.x = B.x + 1;
	u2 = normalize_vector(cross_product(A, B));
	v2 = normalize_vector(cross_product(u2, A));
	l = subtract_vectors(Phit, scene->pl[num].coord);
	angle = acos(dot_product(l, u2) / magnitude(l));
	angle2 = acos(dot_product(l, v2) / magnitude(l));
	if (comp_d(angle, 0.0))
	{
		u = magnitude(l);
		v = 0;
	}
	else if (comp_d(angle, 1.5707963268))
	{
		u = 0;
		v = magnitude(l);
	}
	else
	{
		if (angle > 1.5707963268)
		{
			u2 = multiply_vector(u2, -1);
			angle = acos(dot_product(l, u2) / magnitude(l));
			c = 1;
		}
		if (angle2 < 1.5707963268)
		{
			if (c == 1)
				c = 0;
			else
				c = 1;			
		}
		u = cos(angle) * magnitude(l);
		v = sin(angle) * magnitude(l);
	}
	int u1 = u / scene->checkerboard[HEIGHT];
	u1 = u1 % 2;
	int v0 = v / scene->checkerboard[WIDTH];
	v0 = v0 % 2;
	if (c == 0)
	{
		if ((u1 && v0) || (!u1 && !v0))
			return (0);
		return (1);
	}
	else
	{
		if ((u1 && v0) || (!u1 && !v0))
			return (1);
		return (0);
	}
}
