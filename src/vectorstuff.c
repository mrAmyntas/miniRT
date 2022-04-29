#include "../inc/miniRT.h"

//vector addition
t_vect3d add_vectors(t_vect3d vec1, t_vect3d vec2)
{
	t_vect3d new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	new.z = vec1.z + vec2.z;
	return (new);
}

//Substract vec2 from vec1
t_vect3d subtract_vectors(t_vect3d vec1, t_vect3d vec2)
{
	t_vect3d new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	new.z = vec1.z - vec2.z;
	return (new);
}

//Multiply vec1 by factor
t_vect3d multiply_vector(t_vect3d vec1, double factor)
{
	t_vect3d new;

	new.x = vec1.x * factor;
	new.y = vec1.y * factor;
	new.z = vec1.z * factor;
	return (new);
}

//calculates the dot product of 2 vectors
double	dot_product(t_vect3d vec1, t_vect3d vec2)
{
	double dot_product;

	dot_product = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	return (dot_product);
}

//if there is an intersect, sets vec1 to the coords
bool	intersect_eye_plane(t_scene *scene, t_vect3d *vec1, int num)
{
	double		t;
	t_vect3d	intersect;


	t = dot_product(scene->pl[num].orth_vec, subtract_vectors(scene->pl[num].coord, scene->cam->eye)) / dot_product(scene->pl[num].orth_vec, scene->cam->dir);
	if (t < 0)
		return (false);
	*vec1 = add_vectors(scene->cam->eye, multiply_vector(scene->cam->dir, t));
	return (true);
}

//checks if point P is on plane
bool	is_P_on_plane(t_scene *scene, t_vect3d P, int num)
{
	double		t;
	t_vect3d	vec;

	vec = subtract_vectors(P, scene->pl[num].coord);
	t = dot_product(scene->pl[num].orth_vec, vec);
	if (t == 0)
		return (true);
	return (false);
}

//check if in the current direction the camera ray will intersect with the plane[num]
bool	cast_ray_cam_to_space_check_if_hit_pl(t_scene *scene, int num)
{
	double		t;
	t_vect3d	tmp;

	tmp = subtract_vectors(scene->pl[num].coord, scene->cam->eye);
	tmp = normalize_vector(tmp);
	if (dot_product(scene->pl[num].orth_vec, scene->current_dir) == 0)
	{
		//then the ray is parallel to the plane, and there is no intersection point
		printf("parralel\n");
	}
	t = (dot_product(scene->pl[num].orth_vec, tmp));
	t = t / (dot_product(scene->pl[num].orth_vec, scene->current_dir));
	//t = dot_product(scene->pl[num].orth_vec, subtract_vectors(scene->pl[num].coord, scene->cam->eye)) / dot_product(scene->pl[num].orth_vec, scene->current_dir);
	//printf("t:%f\n", t);
	if (t > 0)
		return (true);
	return (false);
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

//intersection camera ray and plane
//	if N * (P - Q) = 0 -> P is on plane
//  N = plane vector = scene->pl[num]->vec
//  P = Point coords = whatever
//  Q = a point on the plane = scene->pl[num]->coord
//	E = eye coords = scene->cam->coord
//  D = eye vector = scene->cam->vec
// t = N * (Q-E) / N *(D) (?????)
// intersect = E + tD

// |v| = |(x, y, z)| = sqrt( x² + y² + z² )


//A ray is defined by an origin or eye point, E = (x_E, y_E, z_E), and an offset vector, D = (x_D, y_D, z_D). The equation for the ray is:
// P(t) = E + tD	, t>=0

// A plane can be defined by a normal vector, N and a point on the plane, Q.	
// To find the ray/plane intersection :
//
// t = N * (Q-E) / (N * D)

// If t<0 then the plane is behind the eye point and there is no intersection. If t>=0 then the intersection point
// is E + tD. If N*D = 0 then the ray is parallel to the plane, and there is no intersection point.
