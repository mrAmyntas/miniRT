#include "../inc/miniRT.h"

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
double	find_hit_disc(t_scene *scene, t_ray *ray, int *num)
{
	double		*t;
	double		ret;

	t = malloc(sizeof(double) * scene->amount[DISC]);
	calc_t(scene, ray, num, t);
	*num = find_smallest(scene, t, *num, scene->amount[DISC]);
	if (*num != -1)
	{
		ret = t[*num];
		free (t);
		return (ret);
	}
	free (t);
	return (-1);
}
