/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrices.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/23 18:50:14 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

//Matrix x Vertex = TransformedVertex
t_vec4d	matrix44d_x_vert4d(t_matrix44d matrix, t_vec4d vec)
{
	t_vec4d	t;

	t.x = matrix.row1.x * vec.x + matrix.row1.y * vec.y
		+ matrix.row1.z * vec.z + matrix.row1.t * vec.t;
	t.y = matrix.row2.x * vec.x + matrix.row2.y * vec.y
		+ matrix.row2.z * vec.z + matrix.row2.t * vec.t;
	t.z = matrix.row3.x * vec.x + matrix.row3.y * vec.y
		+ matrix.row3.z * vec.z + matrix.row3.t * vec.t;
	t.t = matrix.row4.x * vec.x + matrix.row4.y * vec.y
		+ matrix.row4.z * vec.z + matrix.row4.t * vec.t;
	return (t);
}

//inverted translation matrix
void	set_i_t(t_vect3d *world_coord, t_matrix44d *mat)
{
	mat->row1.x = 1;
	mat->row1.y = 0;
	mat->row1.z = 0;
	mat->row1.t = world_coord->x * -1;
	mat->row2.x = 0;
	mat->row2.y = 1;
	mat->row2.z = 0;
	mat->row2.t = world_coord->y * -1;
	mat->row3.x = 0;
	mat->row3.y = 0;
	mat->row3.z = 1;
	mat->row3.t = world_coord->z * -1;
	mat->row4.x = 0;
	mat->row4.y = 0;
	mat->row4.z = 0;
	mat->row4.t = 1;
}

//rotation matrix (only inverted because we change cylinder vector
//values)
void	set_i_r_val(double a, t_vect3d axis, t_matrix44d *R)
{
	double	c;
	double	s;
	double	t;

	c = cos(a);
	s = sin(a);
	t = 1 - c;
	R->row1.x = c + pow(axis.x, 2) * t;
	R->row1.y = axis.x * axis.y * t - axis.z * s;
	R->row1.z = axis.x * axis.z * t + axis.y * s;
	R->row2.x = axis.y * axis.x * t + axis.z * s;
	R->row2.y = c + pow(axis.y, 2) * t;
	R->row2.z = axis.y * axis.z * t - axis.x * s;
	R->row3.x = axis.z * axis.x * t - axis.y * s;
	R->row3.y = axis.z * axis.y * t + axis.x * s;
	R->row3.z = c + pow(axis.z, 2) * t;
	R->row4.x = 0;
	R->row4.y = 0;
	R->row4.z = 0;
	R->row4.t = 1;
	R->row1.t = 0;
	R->row2.t = 0;
	R->row3.t = 0;
}

void	set_i_r(t_vect3d *obj_dir, t_matrix44d *mat)
{
	t_vect3d	axis;
	t_vect3d	dir;
	t_vect3d	o;
	double		a;

	o.x = 0;
	o.y = 0;
	o.z = 1;
	dir.x = obj_dir->x * -1;
	dir.y = obj_dir->y * -1;
	dir.z = obj_dir->z;
	a = acos(dot_product(o, dir));
	axis = normalize_vector(cross_product(o, dir));
	set_i_r_val(a, axis, mat);
}

void	set_r_tor(t_scene *scene, int num)
{
	scene->tor[num].r.row1.x = scene->tor[num].i_r.row1.x;
	scene->tor[num].r.row1.y = scene->tor[num].i_r.row2.x;
	scene->tor[num].r.row1.z = scene->tor[num].i_r.row3.x;
	scene->tor[num].r.row1.t = scene->tor[num].i_r.row4.x;
	scene->tor[num].r.row2.x = scene->tor[num].i_r.row1.y;
	scene->tor[num].r.row2.y = scene->tor[num].i_r.row2.y;
	scene->tor[num].r.row2.z = scene->tor[num].i_r.row3.y;
	scene->tor[num].r.row2.t = scene->tor[num].i_r.row4.y;
	scene->tor[num].r.row3.x = scene->tor[num].i_r.row1.z;
	scene->tor[num].r.row3.y = scene->tor[num].i_r.row2.z;
	scene->tor[num].r.row3.z = scene->tor[num].i_r.row3.z;
	scene->tor[num].r.row3.t = scene->tor[num].i_r.row4.z;
	scene->tor[num].r.row4.x = scene->tor[num].i_r.row1.t;
	scene->tor[num].r.row4.y = scene->tor[num].i_r.row2.t;
	scene->tor[num].r.row4.z = scene->tor[num].i_r.row3.t;
	scene->tor[num].r.row4.t = scene->tor[num].i_r.row4.t;
}
