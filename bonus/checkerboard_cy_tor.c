/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkerboard_cy_tor.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/30 16:35:24 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"

//finds which points are on/off checker pattern
//takes inner circle (r = centre to side of tube)
//starts from middle top, and takes the length
//from there anti-clockwise around the circle to
//decide in/out pattern.
static int	big_circle(t_scene *scene, t_ray *ray, int *num,
	t_vect3d phit)
{
	t_vect3d	up;
	double		angle;
	double		arclen;
	double		radius;

	up.x = 0.0;
	up.y = 1.0;
	up.z = 0.0;
	radius = scene->tor[*num].r_cir - scene->tor[*num].r_tube;
	angle = acos(dot_product(up, ray->dir) / magnitude(ray->dir));
	if (comp_d(angle, 0.0))
		return (0);
	if (phit.x >= 0)
		angle = M_PI * 2 - angle;
	arclen = angle * radius;
	if ((int)(arclen / (2 * M_PI * radius / scene->cb[H])) % 2)
		return (1);
	return (0);
}

static int	tube_circle(t_scene *scene, int *num,
	t_ray *ray, t_vect3d phit)
{
	t_vect3d	side;
	double		angle;
	double		arclen;

	side = ray->dir;
	ray->dir = normalize_vector(ray->dir);
	ray->eye = add_vectors(scene->origin,
			multiply_vector(ray->dir, scene->tor[*num].r_cir));
	ray->dir = subtract_vectors(phit, ray->eye);
	angle = acos(dot_product(side, ray->dir)
			/ (magnitude(side) * magnitude(ray->dir)));
	if (comp_d(angle, 0.0))
		return (0);
	if (phit.z <= 0.0)
		angle = M_PI * 2 - angle;
	arclen = angle * scene->tor[*num].r_tube;
	if ((int)(arclen / (2 * M_PI * scene->tor[*num].r_tube / scene->cb[W])) % 2)
		return (1);
	return (0);
}

void	checkerboard_tor(t_scene *scene, t_ray *ray, int *num, t_vect3d phit)
{
	int	check;

	ray->eye = scene->origin;
	ray->dir = subtract_vectors(phit, ray->eye);
	ray->dir.z = 0;
	check = big_circle(scene, ray, num, phit);
	if (check == 1)
		scene->tor[*num].checker = 1;
	else
		scene->tor[*num].checker = 0;
	check = tube_circle(scene, num, ray, phit);
	if ((check == 1 && scene->tor[*num].checker == 1)
		|| (check == 0 && scene->tor[*num].checker == 0))
		scene->tor[*num].checker = 1;
	else
		scene->tor[*num].checker = 0;
}

static t_vect3d	find_middle_tube(t_scene *scene, t_vect3d phit, t_vect3d *up)
{
	t_vect3d	z;

	z.x = 0;
	z.y = 0;
	z.z = 1;
	up->x = 0;
	up->y = 1;
	up->z = 0;
	return (add_vectors(scene->origin, multiply_vector(z, phit.z)));
}

//finds a 0/1 value for checkerboard pattern
//cylinder is in origin aligned along z-axis
//the height of the cylinder is used for check[1]
//the length of the arc from the top point to
//phit is used for check[0] (counterclockwise)
int	checkerboard_cy(t_scene *scene, t_vect3d phit, int num)
{
	int			check[2];
	double		angle;
	t_vect3d	middle_tube;
	t_vect3d	up;
	t_vect3d	dir;

	middle_tube = find_middle_tube(scene, phit, &up);
	dir = subtract_vectors(phit, middle_tube);
	angle = acos(dot_product(up, dir) / magnitude(dir));
	if (comp_d(angle, 0.0))
		return (0);
	if (phit.x >= 0)
		angle = M_PI * 2 - angle;
	check[0] = (int)(angle * scene->cy[num].r
			/ (2 * M_PI * scene->cy[num].r / scene->cb[H])) % 2;
	check[1] = (int)(phit.z / (scene->cy[num].height / scene->cb[W])) % 2;
	if ((check[0] && check[1]) || (!check[0] && !check[1]))
		return (1);
	return (0);
}
