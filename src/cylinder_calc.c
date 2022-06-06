#include "../inc/miniRT.h"

//calculate the t_values (distance) of 0, 1, or 2 intersect points
//returns -1 for 0 intersect points
//if one, t[0] and t[1] will be equal
//z values are the z coordinated for the two intersect points.
double	calc_t_0_1(t_scene *scene, t_ray *ray, int *num, double *t)
{
	double	r;
	double	a;
	double	b;
	double	c;
	double	d;

	t[0] = -1;
	t[1] = -1;
	t[2] = -1;
	t[3] = -1;
	r = pow((scene->cy[*num].r), 2);
	a = (pow(ray->dir.x, 2) + pow(ray->dir.y, 2));
	b = (2 * ray->eye.x * ray->dir.x) + (2 * ray->eye.y * ray->dir.y);
	c = pow(ray->eye.x, 2) + pow(ray->eye.y, 2) - r;
	d = pow(b, 2) - (4 * a * c);
	if (d < 0)
		return (-1);
	t[0] = (-b - sqrt(d)) / (2 * a);
	t[1] = (-b + sqrt(d)) / (2 * a);
	return (0);
}

//tests if t1 has a positive value and is between z_values.
//Also tests if it is closer than t2 (if t2 isn't negative)
bool	t_closest(double t1, double t2, double z_m[2], double z)
{
	if (t1 > 0 && (t1 < t2 || t2 < 0 || t2 < z_m[0]
			|| t2 > z_m[1]) && z_m[0]
		< z && z < z_m[1])
		return (true);
	return (false);
}

//t[0] has positive value, is between z_values and is smaller than t[1]
//but we are making a closed finite cylinder, so it might also hit one or
//both of the caps. If it does we calculate this intersection and if it
//hits the cap first we return this distance (t[2] or t[3])
//a cap is hit if the z values lie on different sides of the
//z_min or the z_max
// cap == 0 when hits side. cap == 1 when hits ori/bot cap
// cap == 2 when hits top cap
double	find_intersect(t_ray *ray, t_cy_data cy, int *cap, int set_cap)
{
	if (set_cap == 1)
		*cap = BOT;
	if ((cy.z[0] < cy.z_m[0] && cy.z[1] > cy.z_m[0])
		|| (cy.z[1] < cy.z_m[0] && cy.z[0] > cy.z_m[0]))
	{
		cy.t[2] = (cy.z_m[0] - ray->eye.z) / ray->dir.z;
		if (cy.t[2] < cy.t[0] && cy.t[2] > 0)
			return (cy.t[2]);
	}
	if ((cy.z[0] < cy.z_m[1] && cy.z[1] > cy.z_m[1])
		|| (cy.z[1] < cy.z_m[1] && cy.z[0] > cy.z_m[1]))
	{
		cy.t[3] = (cy.z_m[1] - ray->eye.z) / ray->dir.z;
		if (cy.t[3] < cy.t[0] && cy.t[3] > 0)
		{
			if (set_cap == 1)
				*cap = TOP;
			return (cy.t[3]);
		}
	}
	if (set_cap == 1)
		*cap = NOT;
	return (cy.t[0]);
}

//calculates t_values for top cap and bot cap(which is in ori)
//(P - Q) dot (P - Q) <= r^2 for hitting cap so calculating
//P-Q for both t_values in tmp0 and tmp1
static int	calc_t(t_scene *scene, double *t, t_vect3d *tmp, t_ray *ray)
{
	t_vect3d	top;

	top = scene->origin;
	if (dot_product(scene->ori_dir, ray->dir) == 0)
		return (-1);
	tmp[0] = subtract_vectors(top, ray->eye);
	top.z = t[0];
	tmp[1] = subtract_vectors(top, ray->eye);
	t[0] = (dot_product(scene->ori_dir, tmp[0]))
		/ (dot_product(scene->ori_dir, ray->dir));
	t[1] = (dot_product(scene->ori_dir, tmp[1]))
		/ (dot_product(scene->ori_dir, ray->dir));
	tmp[0] = add_vectors(ray->eye, multiply_vector(ray->dir, t[0]));
	tmp[0] = subtract_vectors(tmp[0], scene->origin);
	tmp[1] = add_vectors(ray->eye, multiply_vector(ray->dir, t[1]));
	tmp[1] = subtract_vectors(tmp[1], top);
	return (0);
}

//calculates if ray hits the cap (basically a disc)
//this would be missed if ray doesnt hit sides within
//valid z ranges
//setting t[2] to radius squared for convenience/norm
double	find_caps(t_scene *scene, int *num, t_ray *ray, int cap)
{
	t_vect3d	tmp[2];
	double		t[3];

	t[0] = scene->cy[*num].height;
	t[2] = pow(scene->cy[*num].r, 2);
	if (calc_t(scene, t, tmp, ray) == -1)
		return (-1);
	if ((t[0] > 0 && dot_product(tmp[0], tmp[0]) <= t[2] && (t[0] < t[1]
				|| t[1] < 0 || (dot_product(tmp[1], tmp[1]) > t[2]))))
	{
		if (cap == 1)
			scene->cy[*num].cap = BOT;
		return (t[0]);
	}
	if (t[1] > 0 && dot_product(tmp[1], tmp[1]) <= t[2])
	{
		if (cap == 1)
			scene->cy[*num].cap = TOP;
		return (t[1]);
	}
	if (cap == 1)
		scene->cy[*num].cap = NOT;
	return (-1);
}
