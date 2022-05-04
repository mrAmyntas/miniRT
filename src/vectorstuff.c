#include "../inc/miniRT.h"

//compare vectors
bool	compare_vectors(t_vect3d vec1, t_vect3d vec2)
{
	if (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
		return (true);
	return (false);
}

//distance between points
double	distance_two_points(t_vect3d P1, t_vect3d P2)
{
	double	d;

	d = pow((pow((P2.x - P1.x), 2) + pow((P2.y - P1.y), 2) + pow((P2.z - P1.z), 2)), 0.5);
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

	if (dot_product(scene->pl[num].orth_vec, scene->cam->dir) == 0)
		return (false);
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
bool	cast_ray_to_space_check_if_hit_pl(t_scene *scene, t_ray *ray, int num)
{
	double		t;
	t_vect3d	tmp;	

	tmp = subtract_vectors(scene->pl[num].coord, ray->eye);
	if (dot_product(scene->pl[num].orth_vec, ray->dir) == 0)
	{
		//then the ray is parallel to the plane, and there is no intersection point
		//printf("parralel\n");
		return (false);
	}
	t = (dot_product(scene->pl[num].orth_vec, tmp)) / (dot_product(scene->pl[num].orth_vec, ray->dir));
	if (t > 0)
	{
		ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t));
		return (true);
	}
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
t_vect3d	mult_vect3d_matrix4x4(t_vect3d vec, t_matrix33d matrix)
{
	t_vect3d new;

	new.x = vec.x * matrix.x.x + vec.y * matrix.x.y + vec.z * matrix.x.z;
	new.y = vec.x * matrix.y.x + vec.y * matrix.y.y + vec.z * matrix.y.z;
	new.z = vec.x * matrix.z.x + vec.y * matrix.z.y + vec.z * matrix.z.z;
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

t_vect3d lookAt(t_scene *scene, t_ray ray)
{
	t_vect3d	new;
	t_matrix33d	matrix;
	t_matrix44d	camToWorld;

	new.x = 0;
	new.y = 1;
	new.z = 0;

	// matrix.x = multiply_vector(scene->cam->dir, -1);
	// matrix.y = cross_product(new, matrix.x);
	// matrix.z = cross_product(matrix.x, matrix.y);
	// new = mult_vect3d_matrix4x4(ray.eye, matrix);

	
//Vec3f right = crossProduct(randomVec, forward); 

// The Look-At Method Limitations
// The method is very simple and works generally well. 
// Though it has an Achilles heels (a weakness). 
// When the camera is vertical looking straight down or straight up, 
// the forward axis gets very close to the arbitrary axis used to compute
//  the right axis. The extreme case is of course when the froward axis
//   and this arbitrary axis are perfectly parallel e.g. when the forward
//    vector is either (0,1,0) or (0,-1,0). Unfortunately in this particular
//     case, the cross product fails producing a result for the right 
// 	vector. There is actually no real solution to this problem. 
// 	You can either detect this case, and choose to set the vectors by 
// 	hand (since you know what the configuration of the vectors should be anyway).
// 	 A more elegant solution can be developed using quaternion interpolation.


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

t_matrix44d	set_camera_to_world(t_vect3d from, t_vect3d to)
{
	t_vect3d	new;
	t_matrix33d	matrix;
	t_matrix44d	camToWorld;

	new.x = 0;
	new.y = 1;
	new.z = 0;
	matrix.x = normalize_vector(subtract_vectors(to, from));
	matrix.y = cross_product(new, matrix.x);
	matrix.z = cross_product(matrix.x, matrix.y);
	camToWorld.x.x = matrix.x.x;
	camToWorld.x.y = matrix.x.y;
	camToWorld.x.z = matrix.x.z;
	camToWorld.y.x = matrix.y.x;
	camToWorld.y.y = matrix.y.y;
	camToWorld.y.z = matrix.y.z;
	camToWorld.z.x = matrix.z.x;
	camToWorld.z.y = matrix.z.y;
	camToWorld.z.z = matrix.z.z;
	camToWorld.t.x = from.x;
	camToWorld.t.y = from.y;
	camToWorld.t.z = from.z;
	camToWorld.x.t = 0;
	camToWorld.y.t = 0;
	camToWorld.z.t = 0;
	camToWorld.t.t = 1;
	return (camToWorld);
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

//returns a ray with its eye same as the camera and direction towards the coords x and y
t_ray	get_ray(t_scene *scene, t_data *data, double x, double y)
{
	t_vect3d LookAtPoint;
	t_vect3d viewDir;
	t_vect3d up;
	t_vect3d V;		
	t_vect3d U;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	// pPOINT SHOULD BE ONE IN 'FRONT'  OF CAMERA, WHICH ISNT ALWAyS z + 1

	LookAtPoint = add_vectors(scene->cam->eye, scene->cam->dir);
	//LookAtPoint = scene->cam->eye;
	//LookAtPoint.z = LookAtPoint.z + 1;// NOW IT ALWAYS LOOKS IN FRONT !!!!
	viewDir = normalize_vector(subtract_vectors(LookAtPoint, scene->cam->eye));
	//viewDir = scene->cam->dir;
	U = normalize_vector(cross_product(viewDir, up));
	V = normalize_vector(cross_product(U, viewDir));

	double viewPlaneHalfWidth= tan(scene->c_fov * M_PI / 180 / 2);
	double aspectRatio = data->height/data->width;
	double viewPlaneHalfHeight = aspectRatio * viewPlaneHalfWidth;
//	t_vect3d viewPlaneBottomLeftPoint = LookAtPoint - V * viewPlaneHalfHeight - U * viewPlaneHalfWidth;
	t_vect3d tmp = subtract_vectors(LookAtPoint, multiply_vector(V, viewPlaneHalfHeight));
	t_vect3d viewPlaneBottomLeftPoint = subtract_vectors(tmp, multiply_vector(U, viewPlaneHalfWidth));
	// xIncVector = (U*2*halfWidth)/xResolution;
	// yIncVector = (V*2*halfHeight)/yResolution;

	tmp = multiply_vector(U, (2 * viewPlaneHalfWidth));
	t_vect3d xIncVector = divide_vec_scalar(tmp, data->width);
	tmp = multiply_vector(V, (2 * viewPlaneHalfHeight));
	t_vect3d yIncVector = divide_vec_scalar(tmp, data->height);

	tmp = add_vectors(viewPlaneBottomLeftPoint, multiply_vector(xIncVector, x));
	t_vect3d ViewPlanePoint = add_vectors(tmp, multiply_vector(yIncVector, y));

	t_ray	ray;
	// CP  -> C - P
	ray.eye = scene->cam->eye;
	ray.dir = normalize_vector(subtract_vectors(ViewPlanePoint, scene->cam->eye));
	return (ray);
}