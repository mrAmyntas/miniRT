/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/23 18:50:24 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/vectors.h"

//calculated the magnitude of a vector
//(the length of the arrow)
double	magnitude(t_vect3d vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

//rotates a ray with the inverted rotation matrix
void	rotate_ray(t_ray *ray, t_matrix44d I_R)
{
	t_vec4d	new_ray_eye;
	t_vec4d	new_ray_dir;

	new_ray_eye.x = ray->eye.x;
	new_ray_eye.y = ray->eye.y;
	new_ray_eye.z = ray->eye.z;
	new_ray_eye.t = 1;
	new_ray_eye = matrix44d_x_vert4d(I_R, new_ray_eye);
	ray->eye.x = new_ray_eye.x;
	ray->eye.y = new_ray_eye.y;
	ray->eye.z = new_ray_eye.z;
	new_ray_dir.x = ray->dir.x;
	new_ray_dir.y = ray->dir.y;
	new_ray_dir.z = ray->dir.z;
	new_ray_dir.t = 0;
	new_ray_dir = matrix44d_x_vert4d(I_R, new_ray_dir);
	ray->dir.x = new_ray_dir.x;
	ray->dir.y = new_ray_dir.y;
	ray->dir.z = new_ray_dir.z;
	normalize_vector(ray->dir);
}

//for torus the normal is calculated with the torus being
//in the origin, aligned along the x-z-axis
//so it needs to be rotated to get the normal in 3d space
//it uses the non-inverted rotation matrix
void	rotate_normal(t_vect3d *N, t_matrix44d R)
{
	t_vec4d	new_ray_dir;

	new_ray_dir.x = N->x;
	new_ray_dir.y = N->y;
	new_ray_dir.z = N->z;
	new_ray_dir.t = 0;
	new_ray_dir = matrix44d_x_vert4d(R, new_ray_dir);
	N->x = new_ray_dir.x;
	N->y = new_ray_dir.y;
	N->z = new_ray_dir.z;
	normalize_vector(*N);
}

//coordinate translation of the ray
void	translate_ray(t_vect3d *eye, t_matrix44d I_T)
{
	t_vec4d	new_eye;

	new_eye.x = eye->x;
	new_eye.y = eye->y;
	new_eye.z = eye->z;
	new_eye.t = 1;
	new_eye = matrix44d_x_vert4d(I_T, new_eye);
	eye->x = new_eye.x;
	eye->y = new_eye.y;
	eye->z = new_eye.z;
}

//returns a ray with its eye same as the camera and
//direction towards the pixelcoords x and y
t_ray	get_ray(t_scene *scene, double x, double y)
{
	scene->r.tmp = add_vectors(scene->r.viewplanebottomleftpoint,
			multiply_vector(scene->r.x_inc_vector, x));
	scene->r.viewplanepoint = add_vectors(
			scene->r.tmp, multiply_vector(scene->r.y_inc_vector, y));
	scene->r.ray.eye = scene->cam->eye;
	scene->r.ray.dir = normalize_vector(
			subtract_vectors(scene->r.viewplanepoint, scene->cam->eye));
	return (scene->r.ray);
}
