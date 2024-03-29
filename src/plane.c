/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/10/11 18:07:40 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	check_if_plane_between_cam_and_light(t_scene *scene, t_vect3d Phit[2])
{
	t_ray	ray;
	int		num2;
	int		num3;
	double	t2[2];

	ray.eye = scene->light->ori;
	ray.dir = normalize_vector(subtract_vectors(Phit[0], ray.eye));
	t2[0] = find_hit_pl(scene, &ray, &num2);
	ray.eye = scene->cam->eye;
	ray.dir = normalize_vector(subtract_vectors(scene->light->ori, ray.eye));
	t2[1] = find_hit_pl(scene, &ray, &num3);
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
//87: checks if plane/ray are parallel
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
double	find_hit_pl(t_scene *scene, t_ray *ray, int *num)
{
	double	*t;
	double	ret;

	t = malloc(sizeof(double) * (unsigned long)scene->amount[PLANE]);
	if (t == NULL)
		ft_error(1, "malloc error in find_hit_pl\n");
	calc_t(scene, ray, num, t);
	*num = find_smallest(t, *num, scene->amount[PLANE]);
	if (*num != -1)
	{
		ret = t[*num];
		free (t);
		return (ret);
	}
	free (t);
	return (-1);
}
