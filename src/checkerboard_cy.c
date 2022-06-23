/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkerboard_cy.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/23 18:49:45 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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
