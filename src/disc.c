#include "../inc/miniRT.h"

static void	set_axis(t_vect3d *axis, t_scene *scene, int num)
{
	t_vect3d	a;
	t_vect3d	b;
	t_vect3d	l;

	a = scene->di[num].orth_vec;
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

//u len 0
//v len 1
//M_PI_2 is 90 degrees (pi / 2 rad)
static int	find_lenghts(t_vect3d l, t_vect3d *axis, double *angle, double *len)
{
	int	c;

	c = 0;
	if (angle[0] > M_PI_2)
	{
		axis[0] = multiply_vector(axis[0], -1);
		angle[0] = acos(dot_product(l, axis[0]) / magnitude(l));
		c = 1;
	}
	if (angle[1] < M_PI_2)
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
int	checkerboard_di(t_scene *scene, t_vect3d Phit, int num)
{
	t_vect3d	l;
	t_vect3d	axis[2];
	double		angle[2];
	double		len[2];

	len[0] = 0;
	len[1] = 0;
	set_axis(axis, scene, num);
	l = subtract_vectors(Phit, scene->di[num].coord);
	angle[0] = acos(dot_product(l, axis[0]) / magnitude(l));
	angle[1] = acos(dot_product(l, axis[1]) / magnitude(l));
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


// calculates the angle light hits Phit on a disc
double	get_di_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		angle;
	t_vect3d	tmp;

	tmp = normalize_vector(subtract_vectors(scene->light[scene->i].ori, Phit));
	angle = acos(dot_product(scene->di[num[1]].orth_vec, tmp)) / (M_PI / 180);
	*N = scene->di[num[1]].orth_vec;
	if (angle > 90)
	{
		angle = 180 - angle;
		*N = multiply_vector(*N, -1);
	}
	return (angle);
}

static void	calc_t(t_scene *scene, t_ray *ray, int *num, double *t)
{
	t_vect3d	tmp;
	t_vect3d	tmp2;

	*num = 0;
	while (*num < scene->amount[DISC])
	{
		tmp = subtract_vectors(scene->di[*num].coord, ray->eye);
		if (dot_product(scene->di[*num].orth_vec, ray->dir) == 0)
		{
			t[*num] = -1;
			*num = *num + 1;
			continue ;
		}
		t[*num] = (dot_product(scene->di[*num].orth_vec, tmp))
			/ (dot_product(scene->di[*num].orth_vec, ray->dir));
		if (t[*num] > 0)
		{
			tmp = add_vectors(ray->eye, multiply_vector(ray->dir, t[*num]));
			tmp2 = subtract_vectors(tmp, scene->di[*num].coord);
			if (dot_product(tmp2, tmp2) > pow(scene->di[*num].r, 2))
				t[*num] = -1;
		}
		*num = *num + 1;
	}
}

//check if the camera ray will hit with the disc[num]
//num is set to closest disc num, distance is returned.
double	find_hit_disc(t_scene *scene, t_ray *ray, int *num, int set)
{
	double		*t;
	double		ret;
	t_vect3d	phit;

	t = malloc(sizeof(double) * scene->amount[DISC]);
	calc_t(scene, ray, num, t);
	*num = find_smallest(t, *num, scene->amount[DISC]);
	if (*num != -1)
	{
		ret = t[*num];
		if (scene->cb[ON] == true && set == 1)
		{
			phit = add_vectors(scene->ray_cam.eye,
					multiply_vector(scene->ray_cam.dir, ret));
			scene->di[*num].checker = checkerboard_pl(scene, phit, *num);
		}

		free (t);
		return (ret);
	}
	free (t);
	return (-1);
}
