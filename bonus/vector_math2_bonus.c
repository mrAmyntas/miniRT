/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math2_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/07/01 16:37:22 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"
#define EPSIL 0.000001

//compare vectors. if same, true
bool	compare_vectors(t_vect3d vec1, t_vect3d vec2)
{
	double	x;
	double	y;
	double	z;

	x = vec1.x - vec2.x;
	if (vec1.x < vec2.x)
		x = vec2.x - vec1.x;
	y = vec1.y - vec2.y;
	if (vec1.y < vec2.y)
		y = vec2.y - vec1.y;
	z = vec1.z - vec2.z;
	if (vec1.z < vec2.z)
		z = vec2.z - vec1.z;
	if (x < EPSIL && y < EPSIL && z < EPSIL)
		return (true);
	return (false);
}

//compare doubles. if same returns true
bool	comp_d(double x, double y)
{
	if (x > y)
		x = x - y;
	else
		x = y - x;
	if (x < EPSIL)
		return (true);
	return (false);
}

//distance between points
double	distance_two_points(t_vect3d P1, t_vect3d P2)
{
	double	d;

	d = pow((pow((P2.x - P1.x), 2) + pow((P2.y - P1.y), 2)
				+ pow((P2.z - P1.z), 2)), 0.5);
	return (d);
}

//divide vector by scalar
t_vect3d	divide_vec_scalar(t_vect3d vec1, double s)
{
	t_vect3d	new;

	if (s == 0)
		return (vec1);
	new.x = vec1.x / s;
	new.y = vec1.y / s;
	new.z = vec1.z / s;
	return (new);
}

//vector addition
t_vect3d	add_vectors(t_vect3d vec1, t_vect3d vec2)
{
	t_vect3d	new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	new.z = vec1.z + vec2.z;
	return (new);
}
