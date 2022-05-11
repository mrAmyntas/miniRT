#include "../inc/miniRT.h"


//print 4x4 double
void	printd_4x4d(double **M)
{
	printf("-----------------------------------------------------\n");
	printf("|%f %f %f %f|\n", M[0][0], M[0][1], M[0][2], M[0][3]);
	printf("|%f %f %f %f|\n", M[1][0], M[1][1], M[1][2], M[1][3]);
	printf("|%f %f %f %f|\n", M[2][0], M[2][1], M[2][2], M[2][3]);
	printf("|%f %f %f %f|\n", M[3][0], M[3][1], M[3][2], M[3][3]);
	printf("-----------------------------------------------------\n");
}

void	scale_pivots(double **M, double **IM)
{
	int	row;
	int	col;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			IM[row][col] /= M[row][row]; 
			col++;
		}
		row++;
	}
}

void	set_mat_to_IM(t_matrix44d *Mat, double **IM)
{
	Mat->row1.x = IM[0][0];
	Mat->row1.y = IM[0][1];
	Mat->row1.z = IM[0][2];
	Mat->row1.t = IM[0][3];
	Mat->row2.x = IM[1][0];
	Mat->row2.y = IM[1][1];
	Mat->row2.z = IM[1][2];
	Mat->row2.t = IM[1][3];
	Mat->row3.x = IM[2][0];
	Mat->row3.y = IM[2][1];
	Mat->row3.z = IM[2][2];
	Mat->row3.t = IM[2][3];
	Mat->row4.x = IM[3][0];
	Mat->row4.y = IM[3][1];
	Mat->row4.z = IM[3][2];
	Mat->row4.t = IM[3][3];
}

//model matrix with new xyz for C
t_matrix44d	matrix_to_translate_to_xyx(t_vect3d C)
{
	t_matrix44d	model;

	model.row1.x = 1;
	model.row1.y = 0;
	model.row1.z = 0;
	model.row1.t = C.x;
	model.row2.x = 0;
	model.row2.y = 1;
	model.row2.z = 0;
	model.row2.t = C.y;
	model.row3.x = 0;
	model.row3.y = 0;
	model.row3.z = 1;
	model.row3.t = C.z;
	model.row4.x = 0;
	model.row4.y = 0;
	model.row4.z = 0;
	model.row4.t = 1;
	return (model);
}

//swaps two rows of 4x8 matrix
void	swap_row(t_vec8d *row1, t_vec8d *row2)
{
	double	tmp;

	tmp = row1->x1;
	row1->x1 = row2->x1;
	row2->x1 = tmp;

	tmp = row1->y1;
	row1->y1 = row2->y1;
	row2->y1 = tmp;

	tmp = row1->z1;
	row1->z1 = row2->z1;
	row2->z1 = tmp;

	tmp = row1->t1;
	row1->t1 = row2->t1;
	row2->t1 = tmp;

	tmp = row1->x2;
	row1->x2 = row2->x2;
	row2->x2 = tmp;

	tmp = row1->y2;
	row1->y2 = row2->y2;
	row2->y2 = tmp;

	tmp = row1->z2;
	row1->z2 = row2->z2;
	row2->z2 = tmp;

	tmp = row1->t2;
	row1->t2 = row2->t2;
	row2->t2 = tmp;

}


void	first_swap(t_matrix48d *M)
{
	if (M->row1.x1 == 0)
	{
		if ((M->row2.x1 != 0) && ((M->row3.x1 == 0) || fabs(M->row3.x1) < fabs(M->row2.x1)) && ((M->row4.x1 == 0) || fabs(M->row4.x1) < fabs(M->row2.x1)))
			swap_row(&M->row1, &M->row2);
		else if ((M->row3.x1 != 0) && ((M->row4.x1 == 0) || fabs(M->row4.x1) < fabs(M->row3.x1)))
			swap_row(&M->row1, &M->row3);
		else if (M->row4.x1 != 0)
			swap_row(&M->row1, &M->row4);
		else
			printf("cant invert this matrix, all 0's in column\n");
	}
}

void	second_swap(t_matrix48d *M)
{
	if (M->row2.y1 == 0)
	{
		if ((M->row3.y1 != 0) && ((M->row4.y1 == 0) || fabs(M->row4.y1) < fabs(M->row3.y1)))
			swap_row(&M->row2, &M->row3);
		else if (M->row4.y1 != 0)
			swap_row(&M->row2, &M->row4);
		else if (M->row1.y1 != 0 && M->row2.x1 != 0)
			swap_row(&M->row2, &M->row1);
		else
			printf("cant invert this matrix, all 0's in column\n");
	}
}

void	third_swap(t_matrix48d *M)
{
	if (M->row3.z1 == 0)
	{
		if (M->row4.z1 != 0)
			swap_row(&M->row3, &M->row4);
		else if (M->row2.z1 != 0 && M->row3.y1 != 0)
			swap_row(&M->row3, &M->row2);
		else if (M->row1.z1 != 0 && M->row3.x1 != 0)
			swap_row(&M->row3, &M->row1);
		else
			printf("cant invert this matrix, all 0's in column\n");
	}
}
void	fourth_swap(t_matrix48d *M)
{
	if (M->row4.t1 == 0)
	{
		if (M->row3.t1 != 0 && M->row4.z1 != 0)
			swap_row(&M->row4, &M->row3);
		else if (M->row2.t1 != 0 && M->row4.y1 != 0)
			swap_row(&M->row4, &M->row2);
		else if (M->row1.t1 != 0 && M->row4.x1 != 0)
			swap_row(&M->row4, &M->row1);
		else
			printf("cant invert this matrix, all 0's in column\n");
	}
}

void set_to_zero(double **M, double **IM)
{
	int		col;
	int		row;
	double	f;
	int		i;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			if (col != row)
			{
				f = M[row][col] / M[col][col];
				if (f != 0)
				{
					i = 0;
					while (i < 4)
					{
						M[row][i] -= f * M[col][i];
						IM[row][i] -= f * IM[col][i];
						i++;
					}
				}
			}
			col++;
		}
		row++;
	}
}

void	set_M(double **M, t_matrix48d *D)
{
	M[0][0] = D->row1.x1;
	M[0][1] = D->row1.y1;
	M[0][2] = D->row1.z1;
	M[0][3] = D->row1.t1;
	M[1][0] = D->row2.x1;
	M[1][1] = D->row2.y1;
	M[1][2] = D->row2.z1;
	M[1][3] = D->row2.t1;
	M[2][0] = D->row3.x1;
	M[2][1] = D->row3.y1;
	M[2][2] = D->row3.z1;
	M[2][3] = D->row3.t1;
	M[3][0] = D->row4.x1;
	M[3][1] = D->row4.y1;
	M[3][2] = D->row4.z1;
	M[3][3] = D->row4.t1;
}

void	set_IM(double **M, t_matrix48d *D)
{
	M[0][0] = D->row1.x2;
	M[0][1] = D->row1.y2;
	M[0][2] = D->row1.z2;
	M[0][3] = D->row1.t2;
	M[1][0] = D->row2.x2;
	M[1][1] = D->row2.y2;
	M[1][2] = D->row2.z2;
	M[1][3] = D->row2.t2;
	M[2][0] = D->row3.x2;
	M[2][1] = D->row3.y2;
	M[2][2] = D->row3.z2;
	M[2][3] = D->row3.t2;
	M[3][0] = D->row4.x2;
	M[3][1] = D->row4.y2;
	M[3][2] = D->row4.z2;
	M[3][3] = D->row4.t2;
}


t_matrix48d	set_D(t_matrix44d *M)
{
	t_matrix48d D;

	D.row1.x1 = M->row1.x;
	D.row1.y1 = M->row1.y;
	D.row1.z1 = M->row1.z;
	D.row1.t1 = M->row1.t;
	D.row2.x1 = M->row2.x;
	D.row2.y1 = M->row2.y;
	D.row2.z1 = M->row2.z;
	D.row2.t1 = M->row2.t;
	D.row3.x1 = M->row3.x;
	D.row3.y1 = M->row3.y;
	D.row3.z1 = M->row3.z;
	D.row3.t1 = M->row3.t;
	D.row4.x1 = M->row4.x;
	D.row4.y1 = M->row4.y;
	D.row4.z1 = M->row4.z;
	D.row4.t1 = M->row4.t;
	D.row1.x2 = 1;
	D.row1.y2 = 0;
	D.row1.z2 = 0;
	D.row1.t2 = 0;
	D.row2.x2 = 0;
	D.row2.y2 = 1; 
	D.row2.z2 = 0;
	D.row2.t2 = 0;
	D.row3.x2 = 0;
	D.row3.y2 = 0;
	D.row3.z2 = 1;
	D.row3.t2 = 0;
	D.row4.x2 = 0;
	D.row4.y2 = 0;
	D.row4.z2 = 0;
	D.row4.t2 = 1;
	return (D);
}

//printfs a 4x4 matrix
void	printf_matrix44d(t_matrix44d matrix)
{
	printf("----------------------\n");
	printf("|%f %f %f %f|\n", matrix.row1.x, matrix.row1.y, matrix.row1.z, matrix.row1.t);
	printf("|%f %f %f %f|\n", matrix.row2.x, matrix.row2.y, matrix.row2.z, matrix.row2.t);
	printf("|%f %f %f %f|\n", matrix.row3.x, matrix.row3.y, matrix.row3.z, matrix.row3.t);
	printf("|%f %f %f %f|\n", matrix.row4.x, matrix.row4.y, matrix.row4.z, matrix.row4.t);
	printf("----------------------\n");
}

//printfs a 4x8 matrix
void	printf_matrix48d(t_matrix48d matrix)
{
	printf("----------------------\n");
	printf("|%f %f %f %f| %f %f %f %f\n", matrix.row1.x1, matrix.row1.y1, matrix.row1.z1, matrix.row1.t1, matrix.row1.x2, matrix.row1.y2, matrix.row1.z2, matrix.row1.t2);
	printf("|%f %f %f %f| %f %f %f %f\n", matrix.row2.x1, matrix.row2.y1, matrix.row2.z1, matrix.row2.t1, matrix.row2.x2, matrix.row2.y2, matrix.row2.z2, matrix.row2.t2);
	printf("|%f %f %f %f| %f %f %f %f\n", matrix.row3.x1, matrix.row3.y1, matrix.row3.z1, matrix.row3.t1, matrix.row3.x2, matrix.row3.y2, matrix.row3.z2, matrix.row3.t2);
	printf("|%f %f %f %f| %f %f %f %f\n", matrix.row4.x1, matrix.row4.y1, matrix.row4.z1, matrix.row4.t1, matrix.row4.x2, matrix.row4.y2, matrix.row4.z2, matrix.row4.t2);
	printf("----------------------\n");
}

//inverts a matrix if possible
t_matrix44d invert_matrix(t_matrix44d *Mat)
{
	t_matrix48d	D;
	double		**M;
	double		**IM;

	M = (double **)malloc(sizeof(double *) * 4);
	IM = (double **)malloc(sizeof(double *) * 4);
	int	i;
	i = 0;
	while (i < 4)
	{
		M[i] = (double *)malloc(sizeof(double) * 4);
		IM[i] = (double *)malloc(sizeof(double) * 4);
		i++;
	}
	D = set_D(Mat);
	first_swap(&D);
	second_swap(&D);
	third_swap(&D);
	fourth_swap(&D);
	set_M(M, &D);
	set_IM(IM, &D);
	set_to_zero(M, IM);
	scale_pivots(M, IM);
	set_mat_to_IM(Mat, IM);
	i = 0;
	while (i < 4)
	{
		free(M[i]);
		free(IM[i]);
		i++;
	}
	free(M);
	free(IM);
	return (*Mat);
}

t_matrix44d	get_inverted_T(t_scene *scene, int num)
{
	t_matrices	M;

	M.T = matrix_to_translate_to_xyx(scene->cy[num].eye);
	M.I_T = invert_matrix(&M.T);
	return (M.I_T);
}





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

void	get_R(double a, t_vect3d axis, t_matrix44d	*R)
{
	R->row1.x = cos(a) + pow(axis.x, 2) * (1 - cos(a));
	R->row1.y = axis.x * axis.y * (1 - cos(a)) - axis.z * sin(a);
	R->row1.z = axis.x * axis.z * (1 - cos(a)) + axis.y * sin(a);
	R->row2.x = axis.y * axis.x * (1 - cos(a)) + axis.z * sin(a);
	R->row2.y = cos(a) + pow(axis.y, 2) * (1 - cos(a));
	R->row2.z = axis.y * axis.z * (1 - cos(a)) - axis.x * sin(a);
	R->row3.x = axis.z * axis.x * (1 - cos(a)) - axis.y * sin(a);
	R->row3.y = axis.z * axis.y * (1 - cos(a)) + axis.x * sin(a);
	R->row3.z = cos(a) + pow(axis.z, 2) * (1 - cos (a)); 
	R->row4.x = 0;
	R->row4.y = 0;
	R->row4.z = 0;
	R->row4.t = 1;
	R->row1.t = 0;
	R->row2.t = 0;
	R->row3.t = 0;
}

t_matrix44d	get_inverted_R(t_scene *scene, int num)
{
	t_vect3d	axis;
	t_vect3d	o;
	double		a;
	t_matrix44d	R;

	o = scene->origin;
	o.z = 1;
	a = acos(dot_product(o, scene->cy[num].dir) / (magnitude(o) * magnitude(scene->cy[num].dir)));
	axis = normalize_vector(cross_product(o, scene->cy[num].dir));
	get_R(a, axis, &R);
	R = invert_matrix(&R);
	return (R);
}
