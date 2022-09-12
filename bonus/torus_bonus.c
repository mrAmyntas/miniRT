/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   torus_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/09/11 15:42:19 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"
#define EPSIL 0.0000001

//finds smallest non-negative t-value and returns which t_value this is
//if none, returns -1
static int	find_smallest_t(long double *t, int num, int amount)
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

//find up to 4 intersect points with the torus
static void	solve_quadratic(t_solve_quartic_var *d, long double *t)
{
	d->d = d->p1 * d->p1 - 4 * d->q1;
	if (d->d > 0.0)
	{
		d->sqd = sqrt((double)d->d);
		t[0] = (-d->p1 + d->sqd) * 0.5;
		t[1] = (-d->p1 - d->sqd) * 0.5;
	}
	d->d = d->p2 * d->p2 - 4 * d->q2;
	if (d->d > 0.0)
	{
		d->sqd = sqrt((double)d->d);
		t[2] = (-d->p2 + d->sqd) * 0.5;
		t[3] = (-d->p2 - d->sqd) * 0.5;
	}
}

//a[0] * t^4 + a[1] * t^3 + a[2] * t^2 + a[3] * t + a[4]
static int	calc_t(t_scene *scene, t_ray *ray, int *num, long double *t)
{
	t_solve_quartic_var	d;

	if (get_a(scene, ray, d.a, num) == -1)
		return (-1);
	d.b[0] = -d.a[2];
	d.b[1] = d.a[1] * d.a[3] - 4.0 * d.a[4];
	d.b[2] = -d.a[1] * d.a[1] * d.a[4] - d.a[3]
		* d.a[3] + 4.0 * d.a[2] * d.a[4];
	d.ret = solve_cubic(&d);
	d.y = d.x[0];
	if (d.ret != 1)
	{
		if (fabsl(d.x[1]) > fabsl(d.y))
			d.y = d.x[1];
		if (fabsl(d.x[2]) > fabsl(d.y))
			d.y = d.x[2];
	}
	d.d = d.y * d.y - 4 * d.a[4];
	solve_quartic(&d);
	solve_quadratic(&d, t);
	return (0);
}

static double	find_closest_tor(t_scene *scene, t_ray *ray,
	int *num, int set_N)
{
	long double		t[4];
	int				ret;
	t_vect3d		phit;

	t[0] = -1;
	t[1] = -1;
	t[2] = -1;
	t[3] = -1;
	translate_ray(&ray->eye, scene->tor[*num].i_t);
	rotate_ray(ray, scene->tor[*num].i_r);
	if (calc_t(scene, ray, num, t) == -1)
		return (-1);
	ret = find_smallest_t(t, 1, 4);
	if (ret < 0)
		return (-1);
	phit = add_vectors(ray->eye, multiply_vector_long(ray->dir, t[ret]));
	if (set_N == 1)
	{
		if (scene->cb[ON] == true)
			checkerboard_tor(scene, ray, num, phit);
		set_normal(scene, num, phit);
	}
	return ((double)t[ret]);
}

double	find_hit_torus(t_scene *scene, t_ray *ray,
	int *num, int set_N)
{
	double	*t;
	t_ray	new_ray;
	double	ret;

	t = malloc(sizeof(double) * (unsigned long)scene->amount[TORUS]);
	if (t == NULL)
		ft_error(1, "malloc error in find_hit_torus\n");
	*num = 0;
	while (*num < scene->amount[TORUS])
	{
		new_ray = *ray;
		t[*num] = find_closest_tor(scene, &new_ray, num, set_N);
		*num = *num + 1;
	}
	*num = find_smallest(t, *num, scene->amount[TORUS]);
	if (*num == -1)
	{
		free (t);
		return (-1);
	}
	ret = t[*num];
	free (t);
	return (ret);
}
