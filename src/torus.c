#include "../inc/miniRT.h"

//0,0,1 torus direction weird (see long distance)
//Phit calcs seem off, something with translation z value and direction being along z-axis
typedef struct s_complex_num{
	double	real;
	double	img;
}			t_complex_num;

double	get_tor_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{

	t_vect3d	tmp;
	double		t;
	double		angle;

	N->x = scene->tor[num[1]].N.x;
	N->y = scene->tor[num[1]].N.y;
	N->z = scene->tor[num[1]].N.z;
	tmp = normalize_vector(subtract_vectors(scene->light[scene->i].ori, Phit));
	t = dot_product(*N, tmp);
	angle = acos(t) / (M_PI / 180);
	return (angle);
}

static void	set_values(t_scene *scene, t_ray *ray, int *num, t_quatric *val)
{
	val->rsq = pow(scene->tor[*num].r_tube, 2);
	val->Rsq = pow(scene->tor[*num].R_cir, 2);
	val->xD = ray->dir.x;
	val->yD = ray->dir.y;
	val->zD = ray->dir.z;
	val->xE = ray->eye.x;
	val->yE = ray->eye.y;
	val->zE = ray->eye.z;
	val->xD2 = pow(ray->dir.x, 2);
	val->yD2 = pow(ray->dir.y, 2);
	val->zD2 = pow(ray->dir.z, 2);
	val->xE2 = pow(ray->eye.x, 2);
	val->yE2 = pow(ray->eye.y, 2);
	val->zE2 = pow(ray->eye.z, 2);
}

//if a[0] is 0, there is no directional vector so cant calculate
//anything meaningfull.
static int	get_a(t_scene *scene, t_ray *ray, double *a, int *num)
{
	t_quatric	val;

	set_values(scene, ray, num, &val);
	a[0] = pow(val.xD, 4) + pow(val.yD, 4) + pow(val.zD, 4) + 2 * val.xD2 * val.yD2 + 2 * val.xD2 * val.zD2 + 2 * val.yD2 * val.zD2;
	if (comp_d(a[0], 0))
		return (-1);
	a[1] = (4 * pow(val.xD, 3) * val.xE + 4 * pow(val.yD, 3) * val.yE + 4 * pow(val.zD, 3) * val.zE + 4 * val.xD2 * val.yD * val.yE + 4 * val.xD2
		* val.zD * val.zE + 4 * val.xD * val.xE * val.yD2 + 4 * val.yD2 * val.zD * val.zE + 4 * val.xD * val.xE * val.zD2 + 4 * val.yD * val.yE * val.zD2) / a[0];

	a[2] = (-2 * val.Rsq * val.xD2 - 2 * val.Rsq * val.yD2 + 2 * val.Rsq * val.zD2 - 2 * val.rsq * val.xD2 - 2 * val.rsq * val.yD2 - 2 * val.rsq * val.zD2 + 6 * val.xD2 * val.xE2 + 2 * val.xE2 * val.yD2
		+ 8 * val.xD * val.xE * val.yD * val.yE + 2 * val.xD2 * val.yE2 + 6 * val.yD2 * val.yE2 + 2 * val.xE2 * val.zD2 + 2 * val.yE2 * val.zD2 + 8 * val.xD * val.xE * val.zD * val.zE
		+ 8 * val.yD * val.yE * val.zD * val.zE + 2 * val.xD2 * val.zE2 + 2 * val.yD2 * val.zE2 + 6 * val.zD2 * val.zE2) / a[0];
	a[3] = (-4 * val.Rsq * val.xD * val.xE - 4 * val.Rsq * val.yD * val.yE + 4 * val.Rsq * val.zD * val.zE - 4 * val.rsq * val.xD * val.xE - 4 * val.rsq * val.yD * val.yE - 4 * val.rsq * val.zD * val.zE + 4 * val.xD * pow(val.xE, 3)
		+ 4 * val.xE2 * val.yD * val.yE + 4 * val.xD * val.xE * val.yE2 + 4 * val.yD * pow(val.yE, 3) + 4 * val.xE2 * val.zD * val.zE + 4 * val.yE2 * val.zD * val.zE + 4 * val.xD * val.xE * val.zE2
		+ 4 * val.yD * val.yE * val.zE2 + 4 * val.zD * pow(val.zE, 3)) / a[0];
	a[4] = (pow(val.Rsq, 2) - 2 * val.Rsq * val.xE2 - 2 * val.Rsq * val.yE2 + 2 * val.Rsq * val.zE2 + pow(val.rsq, 2) - 2 * val.rsq * val.Rsq - 2 * val.rsq * val.xE2 - 2 * val.rsq * val.yE2 - 2 * val.rsq * val.zE2 + pow(val.xE, 4) + pow(val.yE, 4)
		+ pow(val.zE, 4) + 2 * val.xE2 * val.yE2 + 2 * val.xE2 * val.zE2 + 2 * val.yE2 * val.zE2) / a[0];
	return (0);
}

static int	solve_cubic(double *x, double a, double b, double c)
{
	double	a2;
	double	q;
	double	r;
	double	r2;
	double	q3;
	double	A;
	double	B;

	a2 = a * a;
	q = (a2 - 3 * b) / 9;
	r = (a * (2 * a2 - 9 * b) + 27 * c) / 54;
	r2 = r * r;
	q3 = q * q * q;

	if (r2 < q3)
	{
		A = r / sqrt(q3);
		if (A < -1)
			A = -1;
		if (A > 1)
			A = 1;
		A = acos(A);
		a = a / 3;
		q = -2 * sqrt(q);
		x[0] = q * cos(A / 3) - a;
		x[1] = q * cos((A + (M_PI * 2)) / 3) - a;
		x[2] = q * cos((A - (M_PI * 2)) / 3) - a;
		return (3);
	}
	else
	{
		A = -1.0 * pow(fabs(r) + sqrt(r2 - q3), 1.0 / 3);
		if (r < 0)
			A = -A;
		if (comp_d(A, 0) == true)
			B = 0;
		else
			B = q / A;
		a = a / 3;
		x[0] = (A + B) - a;
		x[1] = -0.5 * (A + B) - a;
		x[2] = 0.5 * sqrt(3.0) * (A - B);
		if (fabs(x[2]) < 0.0000001)
		{
			x[2] = x[1];
			return (2);
		}
		return (1);
	}
}

//a[0] * t^4 + a[1] * t^3 + a[2] * t^2 + a[3] * t + a[4]
static int	calc_t(t_scene *scene, t_ray *ray, int *num, double *t)
{
	double	a[5];
	double	b[3];
	double	x[3];
	unsigned int ret;
	t_complex_num complex_num[4];

	if (get_a(scene, ray, a, num) == -1)
		return (-1);
	// a[1] = 4;
	// a[2] = -8;
	// a[3] = 0;
	// a[4] = 1;
	// printf("a:%f %f %f %f\n", a[1], a[2], a[3], a[4]);
	b[0] = -a[2];
	b[1] = a[1] * a[3] - 4.0 * a[4];
	b[2] = -a[1] * a[1] * a[4] - a[3] * a[3] + 4.0 * a[2] * a[4];
	ret = solve_cubic(x, b[0], b[1], b[2]);

	double q1, q2, p1, p2, D, sqD, y;

	y = x[0];
	if (ret != 1)
	{
		if (fabs(x[1]) > fabs(y))
			y = x[1];
		if (fabs(x[2]) > fabs(y))
			y = x[2];
	}

	D = y * y - 4 * a[4];
	if (fabs(D) < 0.0000001)
	{
		q1 = y * 0.5;
		q2 = q1;
		D = a[1] * a[1] - 4 * (a[2] - y);
		if (fabs(D) < 0.0000001)
		{
			p1 = a[1] * 0.5;
			p2 = p1;
		}
		else
		{
			sqD = sqrt(D);
			p1 = (a[1] + sqD) * 0.5;
			p2 = (a[1] - sqD) * 0.5;
		}
	}
	else
	{
		sqD = sqrt(D);
		q1 = (y + sqD) * 0.5;
		q2 = (y - sqD) * 0.5;
		p1 = (a[1] * q1 - a[3]) / (q1 - q2);
		p2 = (a[3] - a[1] * q2) / (q1 - q2);
	}
	
// solving quadratic eq. - x^2 + p1*x + q1 = 0	
	D = p1 * p1 - 4 * q1;
	// printf("D1:%f\n", D);
	if (D < 0.0)
	{
		complex_num[0].real = (-p1 * 0.5);
		complex_num[0].img = sqrt(-D) * 0.5;
		complex_num[1].real = complex_num[0].real;
		complex_num[1].img = -1 * complex_num[0].img;
	}
	else
	{
		// printf("a\n");
		sqD = sqrt(D);
		t[0] = (-p1 + sqD) * 0.5;
		t[1] = (-p1 - sqD) * 0.5;
	}
	D = p2 * p2 - 4 * q2;
	// printf("D2:%f\n", D);
	if (D < 0.0)
	{
		complex_num[2].real = (-p2 * 0.5);
		complex_num[2].img = sqrt(-D) * 0.5;
		complex_num[3].real = complex_num[2].real;
		complex_num[3].img = -1 * complex_num[0].img;
	}
	else
	{
		// printf("b\n");
		sqD = sqrt(D);
		t[2] = (-p2 + sqD) * 0.5;
		t[3] = (-p2 - sqD) * 0.5;
	}
	return 0;
}

static double	find_closest_tor(t_scene *scene, t_ray *ray, int *num)
{
	t_tor_data	tor;
	double		t[4] = {-1, -1, -1, -1};
	double		ret;

	translate_ray(&ray->eye, scene->tor[*num].I_T);
	rotate_ray(ray, scene->tor[*num].I_R);
	if (calc_t(scene, ray, num, t) == -1)
		return (-1);
	// if (t[0] > 0 || t[1] > 0 || t[2] > 0 || t[3] > 0)
	// 	printf("t:%f %f %f %f\n", t[0], t[1], t[2], t[3]);
	ret = find_smallest(scene, t, 1, 4);
	if (ret < 0.0)
		return -1;

	//calc_normal
	t_vect3d 	centre_to_phit;
	t_vect3d	Phit;
	t_vect3d	centre_to_middle_of_tube;
	t_vect3d 	middle_of_tube;
	t_ray		tmp;

	Phit = add_vectors(ray->eye, multiply_vector(ray->dir, ret));
	centre_to_phit = normalize_vector(subtract_vectors(Phit, scene->tor[*num].coord));
	centre_to_middle_of_tube.x = centre_to_phit.x;
	centre_to_middle_of_tube.y = centre_to_phit.y;
	centre_to_middle_of_tube.z = 0;
	middle_of_tube = add_vectors(scene->tor[*num].coord, multiply_vector(centre_to_middle_of_tube, scene->tor[*num].R_cir));
	scene->tor[*num].N = normalize_vector(subtract_vectors(Phit, middle_of_tube));
	// ROTATE THE NORMAL BACK !!!!
	rotate_normal(&scene->tor[*num].N, scene->tor[*num].R);
	return (ret);
}

double	find_hit_torus(t_scene *scene, t_ray *ray, int *num)
{
	double	*t;
	t_ray	new_ray;
	double	ret;

	t = malloc(sizeof(double) * scene->amount[TORUS]);
	*num = 0;
	while (*num < scene->amount[TORUS])
	{
		new_ray = *ray;
		t[*num] = find_closest_tor(scene, &new_ray, num);
		*num = *num + 1;
	}
	*num = find_smallest(scene, t, *num, scene->amount[TORUS]);
	if (*num == -1)
	{
		free (t);
		return (-1);
	}
	ret = t[*num];
	free (t);
	return (ret);

}
