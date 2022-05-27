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

static void	get_a(t_scene *scene, t_ray *ray, double *a, int *num)
{
	t_quatric	val;

	set_values(scene, ray, num, &val);
	a[0] = pow(val.xD, 4) + pow(val.yD, 4) + pow(val.zD, 4) + 2 * val.xD2 * val.yD2 + 2 * val.xD2 * val.zD2 + 2 * val.yD2 * val.zD2;
	a[1] = 4 * pow(val.xD, 3) * val.xE + 4 * pow(val.yD, 3) * val.yE + 4 * pow(val.zD, 3) * val.zE + 4 * val.xD2 * val.yD * val.yE + 4 * val.xD2
		* val.zD * val.zE + 4 * val.xD * val.xE * val.yD2 + 4 * val.yD2 * val.zD * val.zE + 4 * val.xD * val.xE * val.zD2 + 4 * val.yD * val.yE * val.zD2;
	a[2] = -2 * val.Rsq * val.xD2 - 2 * val.Rsq * val.yD2 + 2 * val.Rsq * val.zD2 - 2 * val.rsq * val.xD2 - 2 * val.rsq * val.yD2 - 2 * val.rsq * val.zD2 + 6 * val.xD2 * val.xE2 + 2 * val.xE2 * val.yD2
		+ 8 * val.xD * val.xE * val.yD * val.yE + 2 * val.xD2 * val.yE2 + 6 * val.yD2 * val.yE2 + 2 * val.xE2 * val.zD2 + 2 * val.yE2 * val.zD2 + 8 * val.xD * val.xE * val.zD * val.zE
		+ 8 * val.yD * val.yE * val.zD * val.zE + 2 * val.xD2 * val.zE2 + 2 * val.yD2 * val.zD2 + 6 * val.zD2 * val.zE2;
	a[3] = -4 * val.Rsq * val.xD * val.xE - 4 * val.Rsq * val.yD * val.yE + 4 * val.Rsq * val.zD * val.zE - 4 * val.rsq * val.xD * val.xE - 4 * val.rsq * val.yD * val.yE - 4 * val.rsq * val.zD * val.zE + 4 * val.xD * pow(val.xE, 3)
		+ 4 * val.xE2 * val.yD * val.yE + 4 * val.xD * val.xE * val.yE2 + 4 * val.yD * pow(val.yE, 3) + 4 * val.xE2 * val.zD * val.zE + 4 * val.yE2 * val.zD * val.zE + 4 * val.xD * val.xE * val.zE2
		+ 4 * val.yD * val.yE * val.zE2 + 4 * val.zD * pow(val.zE, 3);
	a[4] = pow(val.Rsq, 2) - 2 * val.Rsq * val.xE2 - 2 * val.Rsq * val.yE2 + 2 * val.Rsq * val.zE2 + pow(val.rsq, 2) - 2 * val.rsq * val.Rsq - 2 * val.rsq * val.xE2 - 2 * val.rsq * val.yE2 - 2 * val.rsq * val.zE2 + pow(val.xE, 4) + pow(val.yE, 4)
		+ pow(val.zE, 4) + 2 * val.xE2 * val.yE2 + 2 * val.xE2 * val.zE2 + 2 * val.yE2 * val.zE2;
}

//a[0] * t^4 + a[1] * t^3 + a[2] * t^2 + a[3] * t + a[4]
static int	calc_t(t_scene *scene, t_ray *ray, int *num, double *t)
{
	double	a[5];

	get_a(scene, ray, a, num);
	if (comp_d(a[0], 0))
		return (-1);
	// if (comp_d(a[4], 0))
	// 	solve_cubic();
	// else
	// 	solve_quatric();
	return 0;
}

static double	find_closest_tor(t_scene *scene, t_ray *ray, int *num)
{
	t_tor_data	tor;
	double		t[4];

	if (calc_t(scene, ray, num, t) == -1)
		return (-1);


	return (0);
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
