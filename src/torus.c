#include "../inc/miniRT.h"

double	get_tor_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	N->x = 0;
	N->y = 0;
	N->z = 0;
	return 45;
}
// div = ( xD4 + yD4 + zD4 + 2 xD2 yD2 + 2 xD2 zD2 + 2 yD2 zD2 ) 
// t^4
// + t^3 ( 4 xD3 xE + 4 yD3 yE + 4 zD3 zE + 4 xD2 yD yE + 4 xD2 zD zE + 4 xD xE yD2 + 4 yD2 zD zE + 4 xD xE zD2 + 4 yD yE zD2 ) / div
// + t^2 ( - 2 R2 xD2 - 2 R2 yD2 + 2 R2 zD2 - 2 r2 xD2 - 2 r2 yD2 - 2 r2 zD2 + 6 xD2 xE2 + 2 xE2 yD2 + 8 xD xE yD yE + 2 xD2 yE2 + 6 yD2 yE2 + 2 xE2 zD2 + 2 yE2 zD2 + 8 xD xE zD zE + 8 yD yE zD zE + 2 xD2 zE2 + 2 yD2 zE2 + 6 zD2 zE2 ) / div
// + t ( - 4 R2 xD xE - 4 R2 yD yE + 4 R2 zD zE - 4 r2 xD xE - 4 r2 yD yE - 4 r2 zD zE + 4 xD xE3 + 4 xE2 yD yE + 4 xD xE yE2 + 4 yD yE3 + 4 xE2 zD zE + 4 yE2 zD zE + 4 xD xE zE2 + 4 yD yE zE2 + 4 zD zE3 ) / div
// + ( R4 - 2 R2 xE2 - 2 R2 yE2 + 2 R2 zE2 + r4 - 2 r2 R2 - 2 r2 xE2 - 2 r2 yE2 - 2 r2 zE2 + xE4 + yE4 + zE4 + 2 xE2 yE2 + 2 xE2 zE2 + 2 yE2 zE2 ) / div = 0




//a[0] * t^4 + a[1] * t^3 + a[2] * t^2 + a[3] * t + a[4]
void	get_a(t_scene *scene, t_ray *ray, double *a)
{
	a[0] = pow(ray->dir.x, 4) + pow(ray->dir.y, 4) + pow(ray->dir.z, 4) + 2 * pow(ray->dir.x, 2) * pow(ray->dir.y, 2) + 2 * pow(ray->dir.x, 2) * pow(ray->dir.z, 2) + 2 * pow(ray->dir.y, 2) * pow(ray->dir.z, 2);
	a[1] = 4 * pow(ray->dir.x, 3) * ray->eye.x + 4 * pow(ray->dir.y, 3) * ray->eye.y + 4 * pow(ray->dir.z, 3) * ray->eye.z + 4 * pow(ray->dir.x, 2) * ray->dir.y * ray->eye.y + 4 * pow(ray->dir.x, 2)
		* ray->dir.z * ray->eye.z + 4 * ray->dir.x * ray->eye.x * pow(ray->dir.y, 2) + 4 * pow(ray->dir.y, 2) * ray->dir.z * ray->eye.z + 4 * ray->dir.x * ray->eye.x * pow(ray->dir.z, 2) + 4 * ray->dir.y * ray->eye.y * pow(ray->dir.z, 2);
	a[2] = 2131231232;
// + t^2 ( - 2 R2 xD2 - 2 R2 yD2 + 2 R2 zD2 - 2 r2 xD2 - 2 r2 yD2 - 2 r2 zD2 + 6 xD2 xE2 + 2 xE2 yD2 + 8 xD xE yD yE + 2 xD2 yE2 + 6 yD2 yE2 + 2 xE2 zD2 + 2 yE2 zD2 + 8 xD xE zD zE + 8 yD yE zD zE + 2 xD2 zE2 + 2 yD2 zE2 + 6 zD2 zE2 ) / div
// + t ( - 4 R2 xD xE - 4 R2 yD yE + 4 R2 zD zE - 4 r2 xD xE - 4 r2 yD yE - 4 r2 zD zE + 4 xD xE3 + 4 xE2 yD yE + 4 xD xE yE2 + 4 yD yE3 + 4 xE2 zD zE + 4 yE2 zD zE + 4 xD xE zE2 + 4 yD yE zE2 + 4 zD zE3 ) / div
// + ( R4 - 2 R2 xE2 - 2 R2 yE2 + 2 R2 zE2 + r4 - 2 r2 R2 - 2 r2 xE2 - 2 r2 yE2 - 2 r2 zE2 + xE4 + yE4 + zE4 + 2 xE2 yE2 + 2 xE2 zE2 + 2 yE2 zE2 ) / div = 0

}

static void	calc_t(t_scene *scene, t_ray *ray, int *num, double *t)
{
	double	a[4];

	get_a(scene, ray, a);


}

static double	find_closest_tor(t_scene *scene, t_ray *ray, int *num)
{
	t_tor_data	tor;
	double		t[4];

	calc_t(scene, ray, num, t);


	return 0;
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
