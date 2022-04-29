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
	//tmp = normalize_vector(subtract_vectors(scene->pl[num].coord, scene->cam->eye));
	if (dot_product(scene->pl[num].orth_vec, scene->current_dir) == 0)
	{
		//then the ray is parallel to the plane, and there is no intersection point
		printf("parralel\n");
		return (false);
	}
	t = (dot_product(scene->pl[num].orth_vec, tmp)) / (dot_product(scene->pl[num].orth_vec, scene->current_dir));
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

//Multiply vector (as 1x3 matrix) with a matrix (3x3)
t_vect3d	mult_vect3d_matrix4x4(t_vect3d vec, t_matrix3x3 matrix)
{
	t_vect3d new;

	new.x = vec.x * matrix.row1.x + vec.y * matrix.row1.y + vec.z * matrix.row1.z;
	new.y = vec.x * matrix.row2.x + vec.y * matrix.row2.y + vec.z * matrix.row2.z;
	new.z = vec.x * matrix.row3.x + vec.y * matrix.row3.y + vec.z * matrix.row3.z;
	return (new);
}

double		magnitude(t_vect3d vec1)
{
	double	result;

	result = sqrt(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z);
	return (result);
}

t_vect3d	cross_product(t_vect3d a, t_vect3d b)
{
	//double		dot_p;
	//double		angle;
	t_vect3d	c;
	//t_vect3d	n;

	//a × b = |a| |b| sin(θ) n
	// dot_p = dot_product(vec1, vec2);
	// angle = arccos(dot_p / (magnitude(vec1) * magnitude(vec2)));
	// for n: a x b means:
	// 	a . n = 0
	// b . n = 0
	// so solve: non zero solutions for these 2 equations
	// 𝑎1𝑛1+𝑎2𝑛2+𝑎3𝑛3=0
	// 𝑏1𝑛1+𝑏2𝑛2+𝑏3𝑛3=0
	// n = ????????????????????
	// result = multiply_vector(n, magnitude(vec1) * magnitude(vec2) * sin(angle));

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.z * b.x) - (a.x * b.z);
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);

}
t_vect3d camera_to_world(t_scene *scene, t_ray ray)
{
	t_vect3d	new;
	t_matrix3x3	matrix;

	new.x = 0;
	new.y = 1;
	new.z = 0;
	matrix.row1 = multiply_vector(scene->cam->dir, -1);
	matrix.row2 = cross_product(new, matrix.row1);
	matrix.row3 = cross_product(matrix.row1, matrix.row2);
	new = mult_vect3d_matrix4x4(ray.eye, matrix);
	return (new);


	// t_matrix	matrix;
	// t_vec3d		forward;
	// t_vec3d		right;
	// t_vec3d		up;

	// forward = vec_multi(camera->vector, -1);
	// right = vec_cross_prod(vec_normalize(vec_new(0, 1, 0)), forward);
	// up = vec_cross_prod(forward, right);
	// matrix.forward = forward;
	// matrix.right = right;
	// matrix.up = up;
	// return (multi_vec_matrix(ray, matrix));

	return (new);
}


//MATRIX

// P'.x = P.x * M00 + P.y * M10 + P.z * M20 + M30; 
// P'.y = P.x * M01 + P.y * M11 + P.z * M21 + M31; 
// P'.z = P.x * M02 + P.y * M12 + P.z * M22 + M32; 
// w'   = P.x * M03 + P.y * M13 + P.z * M23 + M33; 
// if (w' != 1 && w' != 0) { 
//     P'.x /= w', P'.y /= w', P'.z /= w'; 
// } 


// Translation of P is just
// PTx = Px + Tx 
// PTy = Py + Ty 
// PTz = Pz + Tz 

//Rotation is a multiplication with a rotatiom matrix (each row of matrix represents an axis (x - y - z))

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
