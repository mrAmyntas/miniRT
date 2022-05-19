#include "../inc/miniRT.h"

double	find_closest_cy(t_scene *scene, t_ray *ray, int *num, int cap)
{
	t_cy_data	cy;

	transform_ray(scene, ray, num, cy.z_m);
	cy.ret = calc_t_0_1(scene, ray, num, cy.t);
	if (cy.ret == -1)
		return (-1);
	cy.z[0] = ray->eye.z + ray->dir.z * cy.t[0];
	cy.z[1] = ray->eye.z + ray->dir.z * cy.t[1];
	if (t_closest(cy.t[0], cy.t[1], cy.z_m, cy.z[0]))
		return (find_intersect(ray, cy, &scene->cy[*num].cap, cap));
	else if (t_closest(cy.t[1], cy.t[0], cy.z_m, cy.z[1]))
	{
		cy.t[0] = cy.t[1];
		return (find_intersect(ray, cy, &scene->cy[*num].cap, cap));
	}
	else
		return (find_intersect_cap(ray, cy, &scene->cy[*num].cap, cap));
}

double	find_hit_cy(t_scene *scene, t_ray *ray, int *num, int cap)
{
	double	*t;
	t_ray	new_ray;
	double	ret;

	t = malloc(sizeof(double) * scene->amount[2]);
	*num = 0;
	while (*num < scene->amount[2])
	{
		new_ray = *ray;
		t[*num] = find_closest_cy(scene, &new_ray, num, cap);
		*num = *num + 1;
	}
	*num = find_smallest(scene, t, num, scene->amount[2]);
	if (*num == -1)
	{
		free (t);
		return (-1);
	}
	ret = t[*num];
	free (t);
	return (ret);
}
