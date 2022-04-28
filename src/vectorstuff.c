#include "../inc/miniRT.h"

//vector addition
t_vector add_vectors(t_vector vec1, t_vector vec2)
{
	t_vector new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	new.z = vec1.z + vec2.z;
	return (new);
}

//vector substraction
t_vector subtract_vectors(t_vector vec1, t_vector vec2)
{
	t_vector new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	new.z = vec1.z - vec2.z;
	return (new);
}

//vector multiplication
t_vector multiply_vector(t_vector vec1, double factor)
{
	t_vector new;

	new.x = vec1.x * factor;
	new.y = vec1.y * factor;
	new.z = vec1.z * factor;
	return (new);
}

//calculates the dot product of 2 vectors
double	dot_product(t_vector vec1, t_vector vec2)
{
	double dot_product;

	dot_product = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	return (dot_product);
}

//if there is an intersect, sets vec1 to the coords
bool	intersect_eye_plane(t_scene *scene, t_vector *vec1, int num)
{
	double		t;
	t_vector	intersect;


	t = dot_product(scene->pl[num].orth_vec, subtract_vectors(scene->pl[num].coord, scene->cam->eye)) / dot_product(scene->pl[num].orth_vec, scene->cam->dir);
	if (t < 0)
		return (false);
	*vec1 = add_vectors(scene->cam->eye, multiply_vector(scene->cam->dir, t));
	return (true);
}

//checks if point is on plane
bool	is_P_on_plane(t_scene *scene, t_vector P, int num)
{
	double		t;
	t_vector	vec;

	vec = subtract_vectors(P, scene->pl[num].coord);
	t = dot_product(scene->pl[num].orth_vec, vec);
	if (t == 0)
		return (true);
	return (false);
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
