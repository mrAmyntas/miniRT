#include "../inc/miniRT.h"

void	set_normal(t_scene *scene, int *num, t_vect3d phit)
{
	t_vect3d	centre_to_phit;
	t_vect3d	centre_to_middle_of_tube;
	t_vect3d	middle_of_tube;

	centre_to_phit = normalize_vector(subtract_vectors(phit, scene->origin));
	centre_to_middle_of_tube.x = centre_to_phit.x;
	centre_to_middle_of_tube.y = centre_to_phit.y;
	centre_to_middle_of_tube.z = 0;
	middle_of_tube = add_vectors(scene->origin,
			multiply_vector(centre_to_middle_of_tube, scene->tor[*num].R_cir));
	scene->tor[*num].n = normalize_vector(
			subtract_vectors(phit, middle_of_tube));
	rotate_normal(&scene->tor[*num].n, scene->tor[*num].r);
	scene->tor[*num].n = normalize_vector(scene->tor[*num].n);
}

double	get_tor_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	t_vect3d	tmp;
	double		t;
	double		angle;

	N->x = scene->tor[num[1]].n.x;
	N->y = scene->tor[num[1]].n.y;
	N->z = scene->tor[num[1]].n.z;
	tmp = normalize_vector(subtract_vectors(scene->light[scene->i].ori, Phit));
	t = dot_product(*N, tmp);
	angle = acos(t) / (M_PI / 180);
	return (angle);
}

static void	set_values(t_scene *scene, t_ray *ray, int *num, t_quartic *val)
{
	val->r_t2 = pow(scene->tor[*num].r_tube, 2);
	val->r_c2 = pow(scene->tor[*num].R_cir, 2);
	val->xd = ray->dir.x;
	val->yd = ray->dir.y;
	val->zd = ray->dir.z;
	val->xe = ray->eye.x;
	val->ye = ray->eye.y;
	val->ze = ray->eye.z;
	val->xd2 = pow(ray->dir.x, 2);
	val->yd2 = pow(ray->dir.y, 2);
	val->zd2 = pow(ray->dir.z, 2);
	val->xe2 = pow(ray->eye.x, 2);
	val->ye2 = pow(ray->eye.y, 2);
	val->ze2 = pow(ray->eye.z, 2);
}

static void	get_a_1_2(long double *a, t_quartic val)
{
	a[1] = (4 * pow(val.xd, 3) * val.xe + 4 * pow(val.yd, 3) * val.ye + 4
			* pow(val.zd, 3) * val.ze + 4 * val.xd2 * val.yd * val.ye + 4
			* val.xd2 * val.zd * val.ze + 4 * val.xd * val.xe * val.yd2 + 4
			* val.yd2 * val.zd * val.ze + 4 * val.xd * val.xe * val.zd2 + 4
			* val.yd * val.ye * val.zd2) / a[0];
	a[2] = (-2 * val.r_c2 * val.xd2 - 2 * val.r_c2 * val.yd2 + 2 * val.r_c2
			* val.zd2 - 2 * val.r_t2 * val.xd2 - 2 * val.r_t2 * val.yd2 - 2
			* val.r_t2 * val.zd2 + 6 * val.xd2 * val.xe2 + 2 * val.xe2 * val.yd2
			+ 8 * val.xd * val.xe * val.yd * val.ye + 2 * val.xd2 * val.ye2 + 6
			* val.yd2 * val.ye2 + 2 * val.xe2 * val.zd2 + 2 * val.ye2 * val.zd2
			+ 8 * val.xd * val.xe * val.zd * val.ze + 8 * val.yd * val.ye
			* val.zd * val.ze + 2 * val.xd2 * val.ze2 + 2 * val.yd2 * val.ze2
			+ 6 * val.zd2 * val.ze2) / a[0];
}

//if a[0] is 0, there is no directional vector so cant calculate
//anything meaningful.
int	get_a(t_scene *scene, t_ray *ray, long double *a, int *num)
{
	t_quartic	val;

	set_values(scene, ray, num, &val);
	a[0] = pow(val.xd, 4) + pow(val.yd, 4) + pow(val.zd, 4) + 2 * val.xd2
		* val.yd2 + 2 * val.xd2 * val.zd2 + 2 * val.yd2 * val.zd2;
	if (comp_d(a[0], 0))
		return (-1);
	get_a_1_2(a, val);
	a[3] = (-4 * val.r_c2 * val.xd * val.xe - 4 * val.r_c2 * val.yd * val.ye + 4
			* val.r_c2 * val.zd * val.ze - 4 * val.r_t2 * val.xd * val.xe - 4
			* val.r_t2 * val.yd * val.ye - 4 * val.r_t2 * val.zd * val.ze + 4
			* val.xd * pow(val.xe, 3) + 4 * val.xe2 * val.yd * val.ye + 4
			* val.xd * val.xe * val.ye2 + 4 * val.yd * pow(val.ye, 3) + 4
			* val.xe2 * val.zd * val.ze + 4 * val.ye2 * val.zd * val.ze + 4
			* val.xd * val.xe * val.ze2 + 4 * val.yd * val.ye * val.ze2 + 4
			* val.zd * pow(val.ze, 3)) / a[0];
	a[4] = (pow(val.r_c2, 2) - 2 * val.r_c2 * val.xe2 - 2 * val.r_c2 * val.ye2
			+ 2 * val.r_c2 * val.ze2 + pow(val.r_t2, 2) - 2 * val.r_t2
			* val.r_c2 - 2 * val.r_t2 * val.xe2 - 2 * val.r_t2 * val.ye2 - 2
			* val.r_t2 * val.ze2 + pow(val.xe, 4) + pow(val.ye, 4)
			+ pow(val.ze, 4) + 2 * val.xe2 * val.ye2 + 2 * val.xe2 * val.ze2
			+ 2 * val.ye2 * val.ze2) / a[0];
	return (0);
}
