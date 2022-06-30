/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/30 16:36:26 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"

//Substract vec2 from vec1
//(if 2 points, returns direcional vector from vec2 to vec1)
t_vect3d	subtract_vectors(t_vect3d vec1, t_vect3d vec2)
{
	t_vect3d	new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	new.z = vec1.z - vec2.z;
	return (new);
}

//Multiply vec1 by factor
t_vect3d	multiply_vector(t_vect3d vec1, double factor)
{
	t_vect3d	new;

	new.x = vec1.x * factor;
	new.y = vec1.y * factor;
	new.z = vec1.z * factor;
	return (new);
}

//calculates the dot product of 2 vectors
double	dot_product(t_vect3d vec1, t_vect3d vec2)
{
	double	dot_product;

	dot_product = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	return (dot_product);
}

//Normalize a vector
t_vect3d	normalize_vector(t_vect3d vec1)
{
	double		len;
	t_vect3d	new;

	len = sqrt((vec1.x * vec1.x) + (vec1.y * vec1.y) + (vec1.z * vec1.z));
	new.x = vec1.x / len;
	new.y = vec1.y / len;
	new.z = vec1.z / len;
	return (new);
}

//crossproduct of 2 vectors
t_vect3d	cross_product(t_vect3d a, t_vect3d b)
{
	t_vect3d	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.z * b.x) - (a.x * b.z);
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);
}
