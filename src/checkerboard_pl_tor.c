#include "../inc/miniRT.h"

//finds which points are on/off checker pattern
//takes inner circle (r = centre to side of tube)
//starts from middle top, and takes the length
//from there anti-clockwise around the circle to
//decide in/out pattern.
int	big_circle(t_scene *scene, t_ray *ray, int *num,
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
	if ((int)(arclen / (2 * M_PI * radius / scene->cb[H])) % 2)
		return (1);
	return (0);
}

int	tube_circle(t_scene *scene, int *num,
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
	angle = acos(dot_product(side, ray->dir)
			/ (magnitude(side) * magnitude(ray->dir)));
	if (comp_d(angle, 0.0))
		return (0);
	if (phit.z <= 0.0)
		angle = M_PI * 2 - angle;
	arclen = angle * scene->tor[*num].r_tube;
	if ((int)(arclen / (2 * M_PI * scene->tor[*num].r_tube / scene->cb[W])) % 2)
		return (1);
	return (0);
}

static void	set_axis(t_vect3d *axis, t_scene *scene, int num)
{
	t_vect3d	a;
	t_vect3d	b;
	t_vect3d	l;

	a = scene->pl[num].orth_vec;
	b = a;
	if (comp_d(b.x, 0.0))
		b.x = b.x + 0.1;
	else if (comp_d(b.y, 0.0))
		b.y = b.y + 0.1;
	else if (comp_d(b.z, 0.0))
		b.z = b.z + 0.1;
	else
		b.x = b.x + 1;
	axis[0] = normalize_vector(cross_product(a, b));
	axis[1] = normalize_vector(cross_product(axis[0], a));
}

//u len 0
//v len 1
//M_PI_2 is 90 degrees (pi / 2 rad)
static int	find_lenghts(t_vect3d l, t_vect3d *axis, double *angle, double *len)
{
	int	c;

	c = 0;
	if (angle[0] > M_PI_2)
	{
		axis[0] = multiply_vector(axis[0], -1);
		angle[0] = acos(dot_product(l, axis[0]) / magnitude(l));
		c = 1;
	}
	if (angle[1] < M_PI_2)
		c = c + 2;
	len[0] = cos(angle[0]) * magnitude(l);
	len[1] = sin(angle[0]) * magnitude(l);
	if (c == 0 || c == 3)
		return (1);
	return (0);
}

//checks which color pattern the current Phit has
//either returns 1 or 0
//the distances in 2 perpendicular directions are calculated
//both those directions are also perpendicular to the plane 
//vector, so it is like a 3d axis system.
//Based on the distance the point is in these 2 directions
//relative to the original plane coordinates,
//it is either part of a normal or reversed color pattern.
int	checkerboard_pl(t_scene *scene, t_vect3d Phit, int num)
{
	t_vect3d	l;
	t_vect3d	axis[2];
	double		angle[2];
	double		len[2];

	len[0] = 0;
	len[1] = 0;
	set_axis(axis, scene, num);
	l = subtract_vectors(Phit, scene->pl[num].coord);
	angle[0] = acos(dot_product(l, axis[0]) / magnitude(l));
	angle[1] = acos(dot_product(l, axis[1]) / magnitude(l));
	if (find_lenghts(l, axis, angle, len) == 1)
	{
		if ((((int)(len[0] / scene->cb[H]) % 2) && ((int)(len[1] / scene->cb[W])
			% 2)) || (!((int)(len[0] / scene->cb[H]) % 2) && !((int)(len[1]
			/ scene->cb[W]) % 2)))
			return (0);
		return (1);
	}
	if ((((int)(len[0] / scene->cb[H]) % 2) && ((int)(len[1] / scene->cb[W])
		% 2)) || (!((int)(len[0] / scene->cb[H]) % 2) && !((int)(len[1]
			/ scene->cb[W]) % 2)))
		return (1);
	return (0);
}
