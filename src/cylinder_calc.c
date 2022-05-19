#include "../inc/miniRT.h"

//calculate the t_values (distance) of 0, 1, or 2 intersect points
//returns -1 for 0 intersect points
//if one, t[0] and t[1] will be equal
//z values are the z coordinated for the two intersect points.
double	calc_t_0_1(t_scene *scene, t_ray *ray, int *num, double t[4])
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
double	find_intersect(t_ray *ray, t_cy_data cy, int *cap, int set_cap)
{
	if (set_cap == 1)
		*cap = 1;
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
			return (cy.t[3]);
	}
	if (set_cap == 1)
		*cap = 0;
	return (cy.t[0]);
}

//both t_values are outside the z_range of the finite sphere here
//but there might still be legit intersect points, because it could be
//that the rays go through a cap.
//-------> O=====O ------>   (goes through so no t_values)
double	find_intersect_cap(t_ray *ray, t_cy_data cy, int *cap, int set_cap)
{
	if (set_cap == 1)
		*cap = 1;
	if ((cy.z[0] < cy.z_m[0] && cy.z[1] > cy.z_m[0])
		|| (cy.z[1] < cy.z_m[0] && cy.z[0] > cy.z_m[0]))
		cy.t[2] = (cy.z_m[0] - ray->eye.z) / ray->dir.z;
	if ((cy.z[0] < cy.z_m[1] && cy.z[1] > cy.z_m[1])
		|| (cy.z[1] < cy.z_m[1] && cy.z[0] > cy.z_m[1]))
		cy.t[3] = (cy.z_m[1] - ray->eye.z) / ray->dir.z;
	if (cy.t[2] > 0 && (cy.t[2] < cy.t[3] || cy.t[3] < 0))
		return (cy.t[2]);
	else if (cy.t[3] > 0)
		return (cy.t[3]);
	if (set_cap == 1)
		*cap = -1;
	return (-1);
}
