#include "../inc/miniRT.h"

//calculates t_value for each plane
//38: checks if plane/ray are parallel
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
double	find_hit_sq(t_scene *scene, t_ray *ray, int *num)
{
	double		*t;
	double		ret;

	t = malloc(sizeof(double) * scene->amount[PLANE]);
	calc_t(scene, ray, num, t);
	*num = find_smallest(scene, t, *num, scene->amount[PLANE]);
	if (*num != -1)
	{
		ret = t[*num];
		free (t);
		return (ret);
	}
	free (t);
	return (-1);
}
