#include "../inc/miniRT.h"
#include "../inc/vectors.h"

double	magnitude(t_vect3d vec)
{
	return(sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

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

void	rotate_normal(t_vect3d *N, t_matrix44d I_R)
{
	t_vec4d	new_ray_dir;

	new_ray_dir.x = N->x;
	new_ray_dir.y = N->y;
	new_ray_dir.z = N->z;
	new_ray_dir.t = 0;
	new_ray_dir = matrix44d_x_vert4d(I_R, new_ray_dir);
	N->x = new_ray_dir.x;
	N->y = new_ray_dir.y;
	N->z = new_ray_dir.z;
	normalize_vector(*N);
}

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

//translation and rotation of ray and set z-min and z-max.
//the cylinder intersect points are calculated as if it's 
//origin is in the world origin, aligned along the z-axis
//so the ray which comes from the camera in world space
//needs to be translated and rotated with the inverse of
//the translation and rotation that the cylinder has compared
//to its origin position.
//z_m[0] is z_min is 0, z_m[1] is z_max is the height
void	transform_ray(t_scene *scene, t_ray *ray, int *num, double z_m[2])
{
	z_m[0] = 0;
	z_m[1] = scene->cy[*num].height;
	translate_ray(&ray->eye, scene->cy[*num].I_T);
	rotate_ray(ray, scene->cy[*num].I_R);
}

//returns a ray with its eye same as the camera and
//direction towards the pixelcoords x and y
t_ray	get_ray(t_scene *scene, t_data *data, double x, double y)
{
	scene->r.tmp = add_vectors(scene->r.viewPlaneBottomLeftPoint,
			multiply_vector(scene->r.xIncVector, x));
	scene->r.ViewPlanePoint = add_vectors(
			scene->r.tmp, multiply_vector(scene->r.yIncVector, y));
	scene->r.ray.eye = scene->cam->eye;
	scene->r.ray.dir = normalize_vector(
			subtract_vectors(scene->r.ViewPlanePoint, scene->cam->eye));
	return (scene->r.ray);
}
