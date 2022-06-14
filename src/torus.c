#include "../inc/miniRT.h"
#define EPSIL 0.0000001

//find up to 4 intersect points with the torus
static void	solve_quadratic(t_solve_quartic_var *d, double *t)
{
	d->d = d->p1 * d->p1 - 4 * d->q1;
	if (d->d > 0.0)
	{
		d->sqd = sqrt(d->d);
		t[0] = (-d->p1 + d->sqd) * 0.5;
		t[1] = (-d->p1 - d->sqd) * 0.5;
	}
	d->d = d->p2 * d->p2 - 4 * d->q2;
	if (d->d > 0.0)
	{
		d->sqd = sqrt(d->d);
		t[2] = (-d->p2 + d->sqd) * 0.5;
		t[3] = (-d->p2 - d->sqd) * 0.5;
	}
}

//a[0] * t^4 + a[1] * t^3 + a[2] * t^2 + a[3] * t + a[4]
static int	calc_t(t_scene *scene, t_ray *ray, int *num, double *t)
{
	t_solve_quartic_var	d;

	if (get_a(scene, ray, d.a, num) == -1)
		return (-1);
	d.b[0] = -d.a[2];
	d.b[1] = d.a[1] * d.a[3] - 4.0 * d.a[4];
	d.b[2] = -d.a[1] * d.a[1] * d.a[4] - d.a[3]
		* d.a[3] + 4.0 * d.a[2] * d.a[4];
	d.ret = solve_cubic(&d);
	d.y = d.x[0];
	if (d.ret != 1)
	{
		if (fabsl(d.x[1]) > fabsl(d.y))
			d.y = d.x[1];
		if (fabsl(d.x[2]) > fabsl(d.y))
			d.y = d.x[2];
	}
	d.d = d.y * d.y - 4 * d.a[4];
	solve_quartic(&d);
	solve_quadratic(&d, t);
	return (0);
}

//finds which points are on/off checker pattern
//takes inner circle (r = centre to side of tube)
//starts from middle top, and takes the length
//from there anti-clockwise around the circle to
//decide in/out pattern.
static int	big_circle(t_scene *scene, t_ray *ray, int *num,
	t_vect3d phit)
{
	t_vect3d	up;
	double		angle;
	double		arclen;
	double		radius;

	up.x = 0.0;
	up.y = 1.0;
	up.z = 0.0;
	radius = scene->tor[*num].R_cir - scene->tor[*num].r_tube;
	angle = acos(dot_product(up, ray->dir) / magnitude(ray->dir));
	if (comp_d(angle, 0.0))
		return (0);
	if (phit.x >= 0)
		angle = M_PI * 2 - angle;
	arclen = angle * radius;
	if ((int)(arclen / (2 * M_PI * radius / scene->checker[0])) % 2)
		return (1);
	return (0);
}

static int	tube_circle(t_scene *scene, int *num,
	t_ray *ray, t_vect3d phit)
{
	t_vect3d	side;
	double		angle;
	double		arclen;

	side = ray->dir;
	ray->dir = normalize_vector(ray->dir);
	ray->eye = add_vectors(scene->origin,
			multiply_vector(ray->dir, scene->tor[*num].R_cir));
	ray->dir = subtract_vectors(phit, ray->eye);
	// printf("side:%f %f %f    dir:%f %f %f\n", side.x, side.y, side.z, ray->dir.x, ray->dir.y, ray->dir.z);
	angle = acos(dot_product(side, ray->dir) / (magnitude(side) * magnitude(ray->dir)));
	// if (angle < 3)
	// printf("angle:%f\n", angle);
	if (comp_d(angle, 0.0))
		return (0);
	if (phit.z <= 0.0)
		angle = M_PI * 2 - angle;
	arclen = angle * scene->tor[*num].r_tube;
	// printf("len:%f    angle:%f\n", arclen, angle);
	if ((int)(arclen / (2 * M_PI * scene->tor[*num].r_tube / scene->checker[1])) % 2)
		return (1);
	return (0);
}

static void	set_checkerboard(t_scene *scene, t_ray *ray, int *num,
	t_vect3d phit)
{
	int	check;

	ray->eye = scene->origin;
	ray->dir = subtract_vectors(phit, ray->eye);
	ray->dir.z = 0;
	check = big_circle(scene, ray, num, phit);
	if (check == 1)
		scene->tor[*num].checker = 1;
	else
		scene->tor[*num].checker = 0;
	check = tube_circle(scene, num, ray, phit);
	if ((check == 1 && scene->tor[*num].checker == 1) || (check == 0 && scene->tor[*num].checker == 0))
		scene->tor[*num].checker = 1;
	else
		scene->tor[*num].checker = 0;
}

static double	find_closest_tor(t_scene *scene, t_ray *ray,
	int *num, int set_N)
{
	double		t[4];
	int			ret;
	t_vect3d	phit;

	t[0] = -1;
	t[1] = -1;
	t[2] = -1;
	t[3] = -1;
	translate_ray(&ray->eye, scene->tor[*num].i_t);
	rotate_ray(ray, scene->tor[*num].i_r);
	if (calc_t(scene, ray, num, t) == -1)
		return (-1);
	ret = find_smallest(t, 1, 4);
	if (ret < 0)
		return (-1);
	phit = add_vectors(ray->eye, multiply_vector(ray->dir, t[ret]));
	if (set_N == 1)
	{
		// printf("e:%f %f %f    d:%f %f %f\n", ray->eye.x, ray->eye.y, ray->eye.z, ray->dir.x, ray->dir.y, ray->dir.z);
		set_checkerboard(scene, ray, num, phit);
		set_normal(scene, num, phit);
	}
	return (t[ret]);
}

double	find_hit_torus(t_scene *scene, t_ray *ray,
	int *num, int set_N)
{
	double	*t;
	t_ray	new_ray;
	double	ret;

	t = malloc(sizeof(double) * scene->amount[TORUS]);
	*num = 0;
	while (*num < scene->amount[TORUS])
	{
		new_ray = *ray;
		t[*num] = find_closest_tor(scene, &new_ray, num, set_N);
		*num = *num + 1;
	}
	*num = find_smallest(t, *num, scene->amount[TORUS]);
	if (*num == -1)
	{
		free (t);
		return (-1);
	}
	ret = t[*num];
	free (t);
	return (ret);
}
