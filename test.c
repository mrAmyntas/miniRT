#include "inc/miniRT.h"

bool	incr(int *num)
{
	*num = *num + 1;
	return true;
}

int main(void)
{

	double a[2] = {10.0, 1.00};
	double b = 2.5;

	double c = b * -4.*a[0];
	printf("%f\n", c); 

// 	t_vect3d vec2 = {1, 1, 1};
// 	t_vect3d vec1 = {0, 0, 0.1};

// 	printf("%f %f %f\n", vec1.x, vec1.y, vec1.z);

// 	vec1 = normalize_vector(vec1);
// 	//vec2 = normalize_vector(vec2);
// 	printf("%f %f %f\n", vec1.x, vec1.y, vec1.z);

// 	double dot = dot_product(vec1, vec2);
// 	double magf = magnitude(vec1) * magnitude(vec2);


// //	double angle = acos(dot / magf);
// 	double angle = acos(dot_product(vec1, vec2) / (magnitude(vec1) * magnitude(vec2)));

// 	printf(":%f\n", angle);
// 	return 0;
}

//gcc test.c src/vectorstuff.c MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/Users/bhoitzin/.brew/opt/glfw/lib/" -I./inc && ./a.out


	// t_quatric	val;

	// set_values(scene, ray, num, &val);
	// a[0] = pow(val.xD, 4) + pow(val.yD, 4) + pow(val.zD, 4) + 2 * val.xD2 * val.yD2 + 2 * val.xD2 * val.zD2 + 2 * val.yD2 * val.zD2;
	// if (comp_d(a[0], 0))
	// 	return (-1);
	// a[1] = (4 * pow(val.xD, 3) * val.xE + 4 * pow(val.yD, 3) * val.yE + 4 * pow(val.zD, 3) * val.zE + 4 * val.xD2 * val.yD * val.yE + 4 * val.xD2
	// 	* val.zD * val.zE + 4 * val.xD * val.xE * val.yD2 + 4 * val.yD2 * val.zD * val.zE + 4 * val.xD * val.xE * val.zD2 + 4 * val.yD * val.yE * val.zD2) / a[0];

	// a[2] = (-2 * val.Rsq * val.xD2 - 2 * val.Rsq * val.yD2 + 2 * val.Rsq * val.zD2 - 2 * val.rsq * val.xD2 - 2 * val.rsq * val.yD2 - 2 * val.rsq * val.zD2 + 6 * val.xD2 * val.xE2 + 2 * val.xE2 * val.yD2
	// 	+ 8 * val.xD * val.xE * val.yD * val.yE + 2 * val.xD2 * val.yE2 + 6 * val.yD2 * val.yE2 + 2 * val.xE2 * val.zD2 + 2 * val.yE2 * val.zD2 + 8 * val.xD * val.xE * val.zD * val.zE
	// 	+ 8 * val.yD * val.yE * val.zD * val.zE + 2 * val.xD2 * val.zE2 + 2 * val.yD2 * val.zE2 + 6 * val.zD2 * val.zE2) / a[0];
	// a[3] = (-4 * val.Rsq * val.xD * val.xE - 4 * val.Rsq * val.yD * val.yE + 4 * val.Rsq * val.zD * val.zE - 4 * val.rsq * val.xD * val.xE - 4 * val.rsq * val.yD * val.yE - 4 * val.rsq * val.zD * val.zE + 4 * val.xD * pow(val.xE, 3)
	// 	+ 4 * val.xE2 * val.yD * val.yE + 4 * val.xD * val.xE * val.yE2 + 4 * val.yD * pow(val.yE, 3) + 4 * val.xE2 * val.zD * val.zE + 4 * val.yE2 * val.zD * val.zE + 4 * val.xD * val.xE * val.zE2
	// 	+ 4 * val.yD * val.yE * val.zE2 + 4 * val.zD * pow(val.zE, 3)) / a[0];
	// a[4] = (pow(val.Rsq, 2) - 2 * val.Rsq * val.xE2 - 2 * val.Rsq * val.yE2 + 2 * val.Rsq * val.zE2 + pow(val.rsq, 2) - 2 * val.rsq * val.Rsq - 2 * val.rsq * val.xE2 - 2 * val.rsq * val.yE2 - 2 * val.rsq * val.zE2 + pow(val.xE, 4) + pow(val.yE, 4)
	// 	+ pow(val.zE, 4) + 2 * val.xE2 * val.yE2 + 2 * val.xE2 * val.zE2 + 2 * val.yE2 * val.zE2) / a[0];
	// return (0);




//both t_values are outside the z_range of the finite sphere here
//but there might still be legit intersect points, because it could be
//that the rays go through a cap.
//------*-> O=====O ---*--->(goes through and hits sides outside z min/max)
// double	find_intersect_cap(t_ray *ray, t_cy_data cy, int *cap, int set_cap)
// {
// 	if (set_cap == 1)
// 		*cap = BOT;
// 	if ((cy.z[0] < cy.z_m[0] && cy.z[1] > cy.z_m[0])
// 		|| (cy.z[1] < cy.z_m[0] && cy.z[0] > cy.z_m[0]))
// 		cy.t[2] = (cy.z_m[0] - ray->eye.z) / ray->dir.z;
// 	if ((cy.z[0] < cy.z_m[1] && cy.z[1] > cy.z_m[1])
// 		|| (cy.z[1] < cy.z_m[1] && cy.z[0] > cy.z_m[1]))
// 		cy.t[3] = (cy.z_m[1] - ray->eye.z) / ray->dir.z;
// 	if (cy.t[2] > 0 && (cy.t[2] < cy.t[3] || cy.t[3] < 0))
// 		return (cy.t[2]);
// 	else if (cy.t[3] > 0)
// 	{
// 		if (set_cap == 1)
// 			*cap = TOP;			
// 		return (cy.t[3]);
// 	}
// 	if (set_cap == 1)
// 		*cap = NOT;
// 	return (-1);
// }






// double find_closest_cy(t_scene *scene, t_ray *ray, int *num)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	t[4] = {-1, -1, -1 ,-1};
// 	double	D;
// 	double 	r;
// 	double 	zz[2];
// 	double	z_min_max[2];
// 	int		i;
// 	double	intersect[scene->amount[2]];

// 	transform_ray(scene, ray, num, z_min_max);
// 	r = pow((scene->cy[*num].diameter / 2), 2);
// 	a = (pow(ray->dir.x, 2) + pow(ray->dir.y, 2));
// 	b = (2 * ray->eye.x * ray->dir.x) + (2 * ray->eye.y * ray->dir.y);
// 	c = pow(ray->eye.x, 2) + pow(ray->eye.y, 2) - r;
// 	D = pow(b, 2) - (4 * a * c);
// 	if (D < 0)
// 		return (-1);
// 	t[0] = (-b - sqrt(D)) / (2 * a);
// 	t[1] = (-b + sqrt(D)) / (2 * a);
// 	zz[0] = ray->eye.z + ray->dir.z * t[0]; 
// 	zz[1] = ray->eye.z + ray->dir.z * t[1];
// 	if (t[0] > 0 && (t[0] < t[1] || t[1] < 0) && z_min < zz[0] && zz[0] < z_max)
// 	{
// 		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
// 		{
// 			t[2] = (z_min - ray->eye.z) / ray->dir.z;
// 			if (t[2] < t[0] && t[2] > 0)
// 				return t[2];
// 		}
// 		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
// 		{
// 			t[3] = (z_max - ray->eye.z) / ray->dir.z;
// 			if (t[3] < t[0] && t[3] > 0)
// 				return t[3];
// 		}
// 		return (t[0]);
// 	}
// 	else if (z_min < zz[1] && zz[1] < z_max && t[1] > 0)
// 	{
// 		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
// 		{
// 			t[2] = (z_min - ray->eye.z) / ray->dir.z;
// 			if (t[2] < t[1] && t[2] > 0)
// 				return t[2];
// 		}
// 		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
// 		{
// 			t[3] = (z_max - ray->eye.z) / ray->dir.z;
// 			if (t[3] < t[1] && t[3] > 0)
// 				return t[3];
// 		}
// 		return (t[1]);
// 	}
// 	else //outside of z-values
// 	{
// 		t[2] = -1;
// 		t[3] = -1;
// 		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
// 			t[2] = (z_min - ray->eye.z) / ray->dir.z;
// 		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
// 			t[3] = (z_max - ray->eye.z) / ray->dir.z;
// 		if (t[2] > 0 && (t[2] < t[3] || t[3] < 0))
// 			return t[2];
// 		else if (t[3] > 0)
// 			return t[3];
// 	}
// 	return (-1);
// }

// double find_closest_cy(t_scene *scene, t_ray *ray, int *num)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	t[4] = {-1, -1, -1 ,-1};
// 	double	D;
// 	double 	r;
// 	double 	zz[2];
// 	double	z_min;
// 	double	z_max;
// 	int		i;

// 	static int k = 0;
// 	//transform_ray(scene, ray, num, z_min_max);
// 	z_min = 0;
// 	z_max = scene->cy[*num].height;
// 	translate_ray(&ray->eye, scene->cy[*num].I_T);
// 	rotate_ray(ray, scene->cy[*num].I_R);
// 	if (scene->cy[*num].dir.x < 0.001 && scene->cy[*num].dir.y < 0.001
// 		&& scene->cy[*num].dir.z < -0.999999)
// 	{
// 		z_min = scene->cy[*num].height * -1;
// 		z_max = 0;
// 	}
// 	r = pow((scene->cy[*num].diameter / 2), 2);
// 	a = (pow(ray->dir.x, 2) + pow(ray->dir.y, 2));
// 	b = (2 * ray->eye.x * ray->dir.x) + (2 * ray->eye.y * ray->dir.y);
// 	c = pow(ray->eye.x, 2) + pow(ray->eye.y, 2) - r;
// 	D = pow(b, 2) - (4 * a * c);
// 	if (D < 0)
// 		return (-1);
// 	t[0] = (-b - sqrt(D)) / (2 * a);
// 	t[1] = (-b + sqrt(D)) / (2 * a);
// 	zz[0] = ray->eye.z + ray->dir.z * t[0]; 
// 	zz[1] = ray->eye.z + ray->dir.z * t[1];
// 	if (t[0] > 0 && (t[0] < t[1] || t[1] < 0) && z_min < zz[0] && zz[0] < z_max)
// 	{
// 		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
// 		{
// 			t[2] = (z_min - ray->eye.z) / ray->dir.z;
// 			if (t[2] < t[0] && t[2] > 0)
// 				return t[2];
// 		}
// 		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
// 		{
// 			t[3] = (z_max - ray->eye.z) / ray->dir.z;
// 			if (t[3] < t[0] && t[3] > 0)
// 				return t[3];
// 		}
// 		return (t[0]);
// 	}
// 	else if (z_min < zz[1] && zz[1] < z_max && t[1] > 0)
// 	{
// 		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
// 		{
// 			t[2] = (z_min - ray->eye.z) / ray->dir.z;
// 			if (t[2] < t[1] && t[2] > 0)
// 				return t[2];
// 		}
// 		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
// 		{
// 			t[3] = (z_max - ray->eye.z) / ray->dir.z;
// 			if (t[3] < t[1] && t[3] > 0)
// 				return t[3];
// 		}
// 		return (t[1]);
// 	}
// 	else //outside of z-values
// 	{
// 		t[2] = -1;
// 		t[3] = -1;
// 		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
// 			t[2] = (z_min - ray->eye.z) / ray->dir.z;
// 		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
// 			t[3] = (z_max - ray->eye.z) / ray->dir.z;
// 		if (t[2] > 0 && (t[2] < t[3] || t[3] < 0))
// 			return t[2];
// 		else if (t[3] > 0)
// 			return t[3];
// 	}
// 	return (-1);
// }


//returns a ray with its eye same as the camera and direction towards the coords x and y
// t_ray	get_ray(t_scene *scene, t_data *data, double x, double y)
// {
// 	t_vect3d LookAtPoint;
// 	t_vect3d viewDir;
// 	t_vect3d up;
// 	t_vect3d V;		
// 	t_vect3d U;

// 	up.x = 0;
// 	up.y = 1;
// 	up.z = 0;
// 	// pPOINT SHOULD BE ONE IN 'FRONT'  OF CAMERA, WHICH ISNT ALWAyS z + 1

// 	LookAtPoint = add_vectors(scene->cam->eye, scene->cam->dir);
// 	viewDir = normalize_vector(subtract_vectors(LookAtPoint, scene->cam->eye));
// 	U = normalize_vector(cross_product(viewDir, up));
// 	V = normalize_vector(cross_product(U, viewDir));

// 	double viewPlaneHalfWidth= tan(scene->c_fov * M_PI / 180 / 2);
// 	double aspectRatio = data->height/data->width;
// 	double viewPlaneHalfHeight = aspectRatio * viewPlaneHalfWidth;
// 	t_vect3d tmp = subtract_vectors(LookAtPoint, multiply_vector(V, viewPlaneHalfHeight));
// 	t_vect3d viewPlaneBottomLeftPoint = subtract_vectors(tmp, multiply_vector(U, viewPlaneHalfWidth));

// 	tmp = multiply_vector(U, (2 * viewPlaneHalfWidth));
// 	t_vect3d xIncVector = divide_vec_scalar(tmp, data->width);
// 	tmp = multiply_vector(V, (2 * viewPlaneHalfHeight));
// 	t_vect3d yIncVector = divide_vec_scalar(tmp, data->height);

// 	tmp = add_vectors(viewPlaneBottomLeftPoint, multiply_vector(xIncVector, x));
// 	t_vect3d ViewPlanePoint = add_vectors(tmp, multiply_vector(yIncVector, y));

// 	t_ray	ray;
// 	// CP  -> C - P
// 	ray.eye = scene->cam->eye;
// 	ray.dir = normalize_vector(subtract_vectors(ViewPlanePoint, scene->cam->eye));
// 	return (ray);
// }

// //print 4x4 double
// void	printd_4x4d(double **M)
// {
// 	printf("-----------------------------------------------------\n");
// 	printf("|%f %f %f %f|\n", M[0][0], M[0][1], M[0][2], M[0][3]);
// 	printf("|%f %f %f %f|\n", M[1][0], M[1][1], M[1][2], M[1][3]);
// 	printf("|%f %f %f %f|\n", M[2][0], M[2][1], M[2][2], M[2][3]);
// 	printf("|%f %f %f %f|\n", M[3][0], M[3][1], M[3][2], M[3][3]);
// 	printf("-----------------------------------------------------\n");
// }

// void	scale_pivots(double **M, double **IM)
// {
// 	int	row;
// 	int	col;

// 	row = 0;
// 	while (row < 4)
// 	{
// 		col = 0;
// 		while (col < 4)
// 		{
// 			IM[row][col] /= M[row][row]; 
// 			col++;
// 		}
// 		row++;
// 	}
// }

// void	set_mat_to_IM(t_matrix44d *Mat, double **IM)
// {
// 	Mat->row1.x = IM[0][0];
// 	Mat->row1.y = IM[0][1];
// 	Mat->row1.z = IM[0][2];
// 	Mat->row1.t = IM[0][3];
// 	Mat->row2.x = IM[1][0];
// 	Mat->row2.y = IM[1][1];
// 	Mat->row2.z = IM[1][2];
// 	Mat->row2.t = IM[1][3];
// 	Mat->row3.x = IM[2][0];
// 	Mat->row3.y = IM[2][1];
// 	Mat->row3.z = IM[2][2];
// 	Mat->row3.t = IM[2][3];
// 	Mat->row4.x = IM[3][0];
// 	Mat->row4.y = IM[3][1];
// 	Mat->row4.z = IM[3][2];
// 	Mat->row4.t = IM[3][3];
// }

// //T->matrix with new xyz for C
// t_matrix44d	matrix_to_translate_to_xyx(t_vect3d C)
// {
// 	t_matrix44d	T->

// 	T->row1.x = 1;
// 	T->row1.y = 0;
// 	T->row1.z = 0;
// 	T->row1.t = C.x;
// 	T->row2.x = 0;
// 	T->row2.y = 1;
// 	T->row2.z = 0;
// 	T->row2.t = C.y;
// 	T->row3.x = 0;
// 	T->row3.y = 0;
// 	T->row3.z = 1;
// 	T->row3.t = C.z;
// 	T->row4.x = 0;
// 	T->row4.y = 0;
// 	T->row4.z = 0;
// 	T->row4.t = 1;
// 	return (T->;
// }


//inverts a matrix if possible
// t_matrix44d invert_matrix(t_matrix44d *Mat)
// {
// 	t_matrix48d	D;
// 	double		**M;
// 	double		**IM;

// 	M = (double **)malloc(sizeof(double *) * 4);
// 	IM = (double **)malloc(sizeof(double *) * 4);
// 	int	i;
// 	i = 0;
// 	while (i < 4)
// 	{
// 		M[i] = (double *)malloc(sizeof(double) * 4);
// 		IM[i] = (double *)malloc(sizeof(double) * 4);
// 		i++;
// 	}
// 	D = set_D(Mat);
// 	first_swap(&D);
// 	second_swap(&D);
// 	third_swap(&D);
// 	fourth_swap(&D);
// 	set_M(M, &D);
// 	set_IM(IM, &D);
// 	set_to_zero(M, IM); //smth wrong
// 	scale_pivots(M, IM);
// 	set_mat_to_IM(Mat, IM);
// 	i = 0;
// 	while (i < 4)
// 	{
// 		free(M[i]);
// 		free(IM[i]);
// 		i++;
// 	}
// 	free(M);
// 	free(IM);
// //	printf_matrix44d(*Mat);
// 	return (*Mat);
// }

// void	get_inverted_T(t_scene *scene, int num)
// {
// 	t_matrix44d	M;

// 	scene->cy[num].I_T = matrix_to_translate_to_xyx(scene->cy[num].eye);
// 	M = matrix_to_translate_to_xyx(scene->cy[num].eye);
// 	scene->cy[num].I_T = invert_matrix(&M);
// }





    // -----------------------

    // A       = cos(angle_x);
    // B       = sin(angle_x);
    // C       = cos(angle_y);
    // D       = sin(angle_y);
    // E       = cos(angle_z);
    // F       = sin(angle_z);

    // AD      =   A * D;
    // BD      =   B * D;

    // mat[0]  =   C * E;
    // mat[1]  =  -C * F;
    // mat[2]  =   D;
    // mat[4]  =  BD * E + A * F;
    // mat[5]  = -BD * F + A * E;
    // mat[6]  =  -B * C;
    // mat[8]  = -AD * E + B * F;
    // mat[9]  =  AD * F + B * E;
    // mat[10] =   A * C;

    // mat[3]  =  mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
    // mat[15] =  1;

    // -----------------------

// If you want to get the x, y, and z angles between two vectors, 
// take the dot product of the projections of the two vectors onto the orthogonal plane of the axis you want.

// That is, if you want the z-angle between the two vectors, create
// xy-plane vectors of the originals. To do this, make a vector that ignores the z-component of the vectors.

// vec3 u = vec3( ... ); // your input vector
// vec3 v = vec3( ... ); // your other input vector
// float x_angle = acos( dot( u.yz, v.yz ) );
// float y_angle = acos( dot( u.xz, v.xz ) );
// float z_angle = acos( dot( u.xy, v.xy ) );


// //swaps two rows of 4x8 matrix
// void	swap_row(t_vec8d *row1, t_vec8d *row2)
// {
// 	double	tmp;

// 	tmp = row1->x1;
// 	row1->x1 = row2->x1;
// 	row2->x1 = tmp;

// 	tmp = row1->y1;
// 	row1->y1 = row2->y1;
// 	row2->y1 = tmp;

// 	tmp = row1->z1;
// 	row1->z1 = row2->z1;
// 	row2->z1 = tmp;

// 	tmp = row1->t1;
// 	row1->t1 = row2->t1;
// 	row2->t1 = tmp;

// 	tmp = row1->x2;
// 	row1->x2 = row2->x2;
// 	row2->x2 = tmp;

// 	tmp = row1->y2;
// 	row1->y2 = row2->y2;
// 	row2->y2 = tmp;

// 	tmp = row1->z2;
// 	row1->z2 = row2->z2;
// 	row2->z2 = tmp;

// 	tmp = row1->t2;
// 	row1->t2 = row2->t2;
// 	row2->t2 = tmp;

// }

// void	first_swap(t_matrix48d *M)
// {
// 	if (comp_d(M->row1.x1, 0))
// 	{
// 		if ((comp_d(M->row2.x1, 0) == false) && ((comp_d(M->row3.x1, 0)) || fabs(M->row3.x1) < fabs(M->row2.x1)) && ((comp_d(M->row4.x1, 0)) || fabs(M->row4.x1) < fabs(M->row2.x1)))
// 			swap_row(&M->row1, &M->row2);
// 		else if ((comp_d(M->row3.x1, 0) == false) && (comp_d(M->row4.x1, 0) || fabs(M->row4.x1) < fabs(M->row3.x1)))
// 			swap_row(&M->row1, &M->row3);
// 		else if (comp_d(M->row4.x1, 0) == false)
// 			swap_row(&M->row1, &M->row4);
// 		else
// 			printf("cant invert this matrix, all 0's in column\n");
// 	}
// }


// void	second_swap(t_matrix48d *M)
// {
// 	if (comp_d(M->row2.y1, 0))
// 	{
// 		if ((comp_d(M->row3.y1, 0) == false) && ((comp_d(M->row4.y1, 0)) || fabs(M->row4.y1) < fabs(M->row3.y1)))
// 			swap_row(&M->row2, &M->row3);
// 		else if (comp_d(M->row4.y1, 0) == false)
// 			swap_row(&M->row2, &M->row4);
// 		else if (comp_d(M->row1.y1, 0) == false && comp_d(M->row2.x1, 0) == false)
// 			swap_row(&M->row2, &M->row1);
// 		else
// 			printf("cant invert this matrix, all 0's in column\n");
// 	}
// }

// void	third_swap(t_matrix48d *M)
// {
// 	if (comp_d(M->row3.z1, 0))
// 	{
// 		if (comp_d(M->row4.z1, 0) == false)
// 			swap_row(&M->row3, &M->row4);
// 		else if (comp_d(M->row2.z1, 0) == false && comp_d(M->row3.y1, 0) == false)
// 			swap_row(&M->row3, &M->row2);
// 		else if (comp_d(M->row1.z1, 0) == false && comp_d(M->row3.x1, 0) == false)
// 			swap_row(&M->row3, &M->row1);
// 		else
// 			printf("cant invert this matrix, all 0's in column\n");
// 	}
// }

// void	fourth_swap(t_matrix48d *M)
// {
// 	if (comp_d(M->row4.t1, 0))
// 	{
// 		if (comp_d(M->row3.t1, 0) == false && comp_d(M->row4.z1, 0) == false)
// 			swap_row(&M->row4, &M->row3);
// 		else if (comp_d(M->row2.t1, 0) == false && comp_d(M->row4.y1, 0) == false)
// 			swap_row(&M->row4, &M->row2);
// 		else if (comp_d(M->row1.t1, 0) == false && comp_d(M->row4.x1, 0) == false)
// 			swap_row(&M->row4, &M->row1);
// 		else
// 			printf("cant invert this matrix, all 0's in column\n");
// 	}
// }


// void set_to_zero(double **M, double **IM)
// {
// 	int		col;
// 	int		row;
// 	double	f;
// 	int		i;

// 	printd_4x4d(M);
// 	printd_4x4d(IM);

// 	row = 0;
// 	while (row < 4)
// 	{
// 		col = 0;
// 		while (col < 4)
// 		{
// 			if (col != row)
// 			{
// 				f = M[row][col] / M[col][col];
// 				if (f != 0)
// 				{
// 					i = 0;
// 					while (i < 4)
// 					{
// 						M[row][i] = M[row][i] - f * M[col][i];
// 						IM[row][i] = IM[row][i] - f * IM[col][i];
// 						i++;
// 					}
// 				}
// 			}
// 			col++;
// 		}
// 		row++;
// 	}
// 	printd_4x4d(M);
// 	printd_4x4d(IM);
// }

// void	set_M(double **M, t_matrix48d *D)
// {
// 	M[0][0] = D->row1.x1;
// 	M[0][1] = D->row1.y1;
// 	M[0][2] = D->row1.z1;
// 	M[0][3] = D->row1.t1;
// 	M[1][0] = D->row2.x1;
// 	M[1][1] = D->row2.y1;
// 	M[1][2] = D->row2.z1;
// 	M[1][3] = D->row2.t1;
// 	M[2][0] = D->row3.x1;
// 	M[2][1] = D->row3.y1;
// 	M[2][2] = D->row3.z1;
// 	M[2][3] = D->row3.t1;
// 	M[3][0] = D->row4.x1;
// 	M[3][1] = D->row4.y1;
// 	M[3][2] = D->row4.z1;
// 	M[3][3] = D->row4.t1;
// }

// void	set_IM(double **M, t_matrix48d *D)
// {
// 	M[0][0] = D->row1.x2;
// 	M[0][1] = D->row1.y2;
// 	M[0][2] = D->row1.z2;
// 	M[0][3] = D->row1.t2;
// 	M[1][0] = D->row2.x2;
// 	M[1][1] = D->row2.y2;
// 	M[1][2] = D->row2.z2;
// 	M[1][3] = D->row2.t2;
// 	M[2][0] = D->row3.x2;
// 	M[2][1] = D->row3.y2;
// 	M[2][2] = D->row3.z2;
// 	M[2][3] = D->row3.t2;
// 	M[3][0] = D->row4.x2;
// 	M[3][1] = D->row4.y2;
// 	M[3][2] = D->row4.z2;
// 	M[3][3] = D->row4.t2;
// }


// t_matrix48d	set_D(t_matrix44d *M)
// {
// 	t_matrix48d D;

// 	D.row1.x1 = M->row1.x;
// 	D.row1.y1 = M->row1.y;
// 	D.row1.z1 = M->row1.z;
// 	D.row1.t1 = M->row1.t;
// 	D.row2.x1 = M->row2.x;
// 	D.row2.y1 = M->row2.y;
// 	D.row2.z1 = M->row2.z;
// 	D.row2.t1 = M->row2.t;
// 	D.row3.x1 = M->row3.x;
// 	D.row3.y1 = M->row3.y;
// 	D.row3.z1 = M->row3.z;
// 	D.row3.t1 = M->row3.t;
// 	D.row4.x1 = M->row4.x;
// 	D.row4.y1 = M->row4.y;
// 	D.row4.z1 = M->row4.z;
// 	D.row4.t1 = M->row4.t;
// 	D.row1.x2 = 1;
// 	D.row1.y2 = 0;
// 	D.row1.z2 = 0;
// 	D.row1.t2 = 0;
// 	D.row2.x2 = 0;
// 	D.row2.y2 = 1; 
// 	D.row2.z2 = 0;
// 	D.row2.t2 = 0;
// 	D.row3.x2 = 0;
// 	D.row3.y2 = 0;
// 	D.row3.z2 = 1;
// 	D.row3.t2 = 0;
// 	D.row4.x2 = 0;
// 	D.row4.y2 = 0;
// 	D.row4.z2 = 0;
// 	D.row4.t2 = 1;
// 	return (D);
// }
//printfs a 4x4 matrix
// void	printf_matrix44d(t_matrix44d matrix)
// {
// 	printf("----------------------\n");
// 	printf("|%f %f %f %f|\n", matrix.row1.x, matrix.row1.y, matrix.row1.z, matrix.row1.t);
// 	printf("|%f %f %f %f|\n", matrix.row2.x, matrix.row2.y, matrix.row2.z, matrix.row2.t);
// 	printf("|%f %f %f %f|\n", matrix.row3.x, matrix.row3.y, matrix.row3.z, matrix.row3.t);
// 	printf("|%f %f %f %f|\n", matrix.row4.x, matrix.row4.y, matrix.row4.z, matrix.row4.t);
// 	printf("----------------------\n");
// }

// //printfs a 4x8 matrix
// void	printf_matrix48d(t_matrix48d matrix)
// {
// 	printf("----------------------\n");
// 	printf("|%f %f %f %f| %f %f %f %f\n", matrix.row1.x1, matrix.row1.y1, matrix.row1.z1, matrix.row1.t1, matrix.row1.x2, matrix.row1.y2, matrix.row1.z2, matrix.row1.t2);
// 	printf("|%f %f %f %f| %f %f %f %f\n", matrix.row2.x1, matrix.row2.y1, matrix.row2.z1, matrix.row2.t1, matrix.row2.x2, matrix.row2.y2, matrix.row2.z2, matrix.row2.t2);
// 	printf("|%f %f %f %f| %f %f %f %f\n", matrix.row3.x1, matrix.row3.y1, matrix.row3.z1, matrix.row3.t1, matrix.row3.x2, matrix.row3.y2, matrix.row3.z2, matrix.row3.t2);
// 	printf("|%f %f %f %f| %f %f %f %f\n", matrix.row4.x1, matrix.row4.y1, matrix.row4.z1, matrix.row4.t1, matrix.row4.x2, matrix.row4.y2, matrix.row4.z2, matrix.row4.t2);
// 	printf("----------------------\n");
// }

	//t[3] = smallest(t);
	// if (comp_d(t[0], t[3]) && t[0] > 0)
	// {
	// 	num[0] = PLANE;
	// 	num[1] = numb[0];
	// }
	// else if (comp_d(t[1], t[3]) && t[1] > 0)
	// {
	// 	num[0] = CYLINDER;
	// 	num[1] = numb[1];
	// }
	// else if (comp_d(t[2], t[3]) && t[2] > 0)
	// {
	// 	num[0] = SPHERE;
	// 	num[1] = numb[2];
	// }

	// a[0] = pow(ray->dir.x, 4) + pow(ray->dir.y, 4) + pow(ray->dir.z, 4) + 2 * pow(ray->dir.x, 2) * pow(ray->dir.y, 2) + 2 * pow(ray->dir.x, 2) * pow(ray->dir.z, 2) + 2 * pow(ray->dir.y, 2) * pow(ray->dir.z, 2);
	// a[1] = 4 * pow(ray->dir.x, 3) * ray->eye.x + 4 * pow(ray->dir.y, 3) * ray->eye.y + 4 * pow(ray->dir.z, 3) * ray->eye.z + 4 * pow(ray->dir.x, 2) * ray->dir.y * ray->eye.y + 4 * pow(ray->dir.x, 2)
	// 	* ray->dir.z * ray->eye.z + 4 * ray->dir.x * ray->eye.x * pow(ray->dir.y, 2) + 4 * pow(ray->dir.y, 2) * ray->dir.z * ray->eye.z + 4 * ray->dir.x * ray->eye.x * pow(ray->dir.z, 2) + 4 * ray->dir.y * ray->eye.y * pow(ray->dir.z, 2);
	// a[2] = -2 * Rsq * pow(ray->dir.x, 2) - 2 * Rsq * pow(ray->dir.y, 2) + 2 * Rsq * pow(ray->dir.z, 2) - 2 * rsq * pow(ray->dir.x, 2) - 2 * rsq * pow(ray->dir.y, 2) - 2 * rsq * pow(ray->dir.z, 2) + 6 * pow(ray->dir.x, 2) * pow(ray->eye.x, 2) + 2 * pow(ray->eye.x, 2) * pow(ray->dir.y, 2)
	// 	+ 8 * ray->dir.x * ray->eye.x * ray->dir.y * ray->eye.y + 2 * pow(ray->dir.x, 2) * pow(ray->eye.y, 2) + 6 * pow(ray->dir.y, 2) * pow(ray->eye.y, 2) + 2 * pow(ray->eye.x, 2) * pow(ray->dir.z, 2) + 2 * pow(ray->eye.y, 2) * pow(ray->dir.z, 2) + 8 * ray->dir.x * ray->eye.x * ray->dir.z * ray->eye.z
	// 	+ 8 * ray->dir.y * ray->eye.y * ray->dir.z * ray->eye.z + 2 * pow(ray->dir.x, 2) * pow(ray->eye.z, 2) + 2 * pow(ray->dir.y, 2) * pow(ray->dir.z, 2) + 6 * pow(ray->dir.z, 2) * pow(ray->eye.z, 2);
	// a[3] = -4 * Rsq * ray->dir.x * ray->eye.x - 4 * Rsq * ray->dir.y * ray->eye.y + 4 * Rsq * ray->dir.z * ray->eye.z - 4 * rsq * ray->dir.x * ray->eye.x - 4 * rsq * ray->dir.y * ray->eye.y - 4 * rsq * ray->dir.z * ray->eye.z + 4 * ray->dir.x * pow(ray->eye.x, 3)
	// 	+ 4 * pow(ray->eye.x, 2) * ray->dir.y * ray->eye.y + 4 * ray->dir.x * ray->eye.x * pow(ray->eye.y, 2) + 4 * ray->dir.y * pow(ray->eye.y, 3) + 4 * pow(ray->eye.x, 2) * ray->dir.z * ray->eye.z + 4 * pow(ray->eye.y, 2) * ray->dir.z * ray->eye.z + 4 * ray->dir.x * ray->eye.x * pow(ray->eye.z, 2)
	// 	+ 4 * ray->dir.y * ray->eye.y * pow(ray->eye.z, 2) + 4 * ray->dir.z * pow(ray->eye.z, 3);
	// a[4] = pow(Rsq, 2) - 2 * Rsq * pow(ray->eye.x, 2) - 2 * Rsq * pow(ray->eye.y, 2) + 2 * Rsq * pow(ray->eye.z, 2) + pow(rsq, 2) - 2 * rsq * Rsq - 2 * rsq * pow(ray->eye.x, 2) - 2 * rsq * pow(ray->eye.y, 2) - 2 * rsq * pow(ray->eye.z, 2) + pow(ray->eye.x, 4) + pow(ray->eye.y, 4)
	// 	+ pow(ray->eye.z, 4) + 2 * pow(ray->eye.x, 2) * pow(ray->eye.y, 2) + 2 * pow(ray->eye.x, 2) * pow(ray->eye.z, 2) + 2 * pow(ray->eye.y, 2) * pow(ray->eye.z, 2);
