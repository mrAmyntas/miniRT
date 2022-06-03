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
void	set_i_t(t_scene *scene, int num)
{
	scene->cy[num].I_T.row1.x = 1;
	scene->cy[num].I_T.row1.y = 0;
	scene->cy[num].I_T.row1.z = 0;
	scene->cy[num].I_T.row1.t = scene->cy[num].eye.x * -1;
	scene->cy[num].I_T.row2.x = 0;
	scene->cy[num].I_T.row2.y = 1;
	scene->cy[num].I_T.row2.z = 0;
	scene->cy[num].I_T.row2.t = scene->cy[num].eye.y * -1;
	scene->cy[num].I_T.row3.x = 0;
	scene->cy[num].I_T.row3.y = 0;
	scene->cy[num].I_T.row3.z = 1;
	scene->cy[num].I_T.row3.t = scene->cy[num].eye.z * -1;
	scene->cy[num].I_T.row4.x = 0;
	scene->cy[num].I_T.row4.y = 0;
	scene->cy[num].I_T.row4.z = 0;
	scene->cy[num].I_T.row4.t = 1;
}

//inverted translation matrix for torus stuff optimize with 1 funct, not one per object
void	set_i_t_tor(t_scene *scene, int num)
{
	scene->tor[num].I_T.row1.x = 1;
	scene->tor[num].I_T.row1.y = 0;
	scene->tor[num].I_T.row1.z = 0;
	scene->tor[num].I_T.row1.t = scene->tor[num].coord.x * -1;
	scene->tor[num].I_T.row2.x = 0;
	scene->tor[num].I_T.row2.y = 1;
	scene->tor[num].I_T.row2.z = 0;
	scene->tor[num].I_T.row2.t = scene->tor[num].coord.y * -1;
	scene->tor[num].I_T.row3.x = 0;
	scene->tor[num].I_T.row3.y = 0;
	scene->tor[num].I_T.row3.z = 1;
	scene->tor[num].I_T.row3.t = scene->tor[num].coord.z * -1;
	scene->tor[num].I_T.row4.x = 0;
	scene->tor[num].I_T.row4.y = 0;
	scene->tor[num].I_T.row4.z = 0;
	scene->tor[num].I_T.row4.t = 1;
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

void	set_i_r(t_scene *scene, int num)
{
	t_vect3d	axis;
	t_vect3d	dir;
	t_vect3d	o;
	double		a;

	o.x = 0;
	o.y = 0;
	o.z = 1;
	dir.x = scene->cy[num].dir.x * -1;
	dir.y = scene->cy[num].dir.y * -1;
	dir.z = scene->cy[num].dir.z;
	a = acos(dot_product(o, dir));
	axis = normalize_vector(cross_product(o, dir));
	set_i_r_val(a, axis, &scene->cy[num].I_R);
}


void	set_i_r_tor(t_scene *scene, int num)
{
	t_vect3d	axis;
	t_vect3d	dir;
	t_vect3d	o;
	double		a;

	o.x = 0;
	o.y = 0;
	o.z = 1;
	dir.x = scene->tor[num].dir.x * -1;
	dir.y = scene->tor[num].dir.y * -1;
	dir.z = scene->tor[num].dir.z;
	a = acos(dot_product(o, dir));
	axis = normalize_vector(cross_product(o, dir));
	set_i_r_val(a, axis, &scene->tor[num].I_R);
}

void	set_r_tor(t_scene *scene, int num)
{
	scene->tor[num].R.row1.x = scene->tor[num].I_R.row1.x;
	scene->tor[num].R.row1.y = scene->tor[num].I_R.row2.x;
	scene->tor[num].R.row1.z = scene->tor[num].I_R.row3.x;
	scene->tor[num].R.row1.t = scene->tor[num].I_R.row4.x;
	scene->tor[num].R.row2.x = scene->tor[num].I_R.row1.y;
	scene->tor[num].R.row2.y = scene->tor[num].I_R.row2.y;
	scene->tor[num].R.row2.z = scene->tor[num].I_R.row3.y;
	scene->tor[num].R.row2.t = scene->tor[num].I_R.row4.y;
	scene->tor[num].R.row3.x = scene->tor[num].I_R.row1.z;
	scene->tor[num].R.row3.y = scene->tor[num].I_R.row2.z;
	scene->tor[num].R.row3.z = scene->tor[num].I_R.row3.z;
	scene->tor[num].R.row3.t = scene->tor[num].I_R.row4.z;
	scene->tor[num].R.row4.x = scene->tor[num].I_R.row1.t;
	scene->tor[num].R.row4.y = scene->tor[num].I_R.row2.t;
	scene->tor[num].R.row4.z = scene->tor[num].I_R.row3.t;
	scene->tor[num].R.row4.t = scene->tor[num].I_R.row4.t;
}

void	printf_matrix44d(t_matrix44d m)
{
	printf("----------------------\n");
	printf("|%f %f %f %f|\n", m.row1.x, m.row1.y, m.row1.z, m.row1.t);
	printf("|%f %f %f %f|\n", m.row2.x, m.row2.y, m.row2.z, m.row2.t);
	printf("|%f %f %f %f|\n", m.row3.x, m.row3.y, m.row3.z, m.row3.t);
	printf("|%f %f %f %f|\n", m.row4.x, m.row4.y, m.row4.z, m.row4.t);
	printf("----------------------\n");
}
