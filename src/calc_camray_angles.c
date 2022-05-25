#include "../inc/miniRT.h"

static double	get_angle_sp(t_scene *scene, t_vect3d Phit, int *num)
{
	double		angle;
	t_ray		ray;
	t_vect3d	N;

    N = normalize_vector(subtract_vectors(Phit, scene->sp[num[1]].C));
	ray.dir = normalize_vector(subtract_vectors(scene->cam->eye, Phit));
    angle = acos(dot_product(N, ray.dir)) * (180 / M_PI);
	return (angle);
}

static double	get_angle_side_cy(t_scene *scene, int num[2], t_vect3d Phit)
{
	double		t;
	double		angle;
	t_vect3d	tmp;
	t_vect3d	N;

	t = magnitude(subtract_vectors(Phit, scene->cy[num[1]].eye));
	t = fabs((t * t) - (scene->cy[num[1]].r * scene->cy[num[1]].r));
	t = sqrt(t);
   	tmp = add_vectors(scene->cy[num[1]].eye, multiply_vector(scene->cy[num[1]].dir, t));
   	N = normalize_vector(subtract_vectors(Phit, tmp));
	tmp = normalize_vector(subtract_vectors(scene->cam->eye, Phit));
	t = dot_product(N, tmp);
	angle = acos(t) / (M_PI / 180);
	return (angle);
}

static double	get_angle_cy(t_scene *scene, t_vect3d Phit, int *num)
{
	double		angle;
	double		t;
	t_vect3d	tmp;
	t_vect3d	N;

	if (scene->cy[num[1]].cap > 0)
	{
		if (scene->cy[num[1]].cap == 1)
			N = multiply_vector(scene->cy[num[1]].dir, -1);
		else
			N = scene->cy[num[1]].dir;
		tmp = normalize_vector(subtract_vectors(scene->cam->eye, Phit));
		angle = acos(dot_product(N, tmp)) / (M_PI / 180);
	}
	else
		angle = get_angle_side_cy(scene, num, Phit);
	return (angle);

}

// finds the right function to calculate the angle between 
// Phit->cam   and normal
// if this is > 90, then camera has to be inside the obj 
double	get_camray_angle(t_scene *scene, t_vect3d *Phit, int *num)
{
	if (num[0] == CYLINDER)
		return (get_angle_cy(scene, Phit[0], num));
	if (num[0] == SPHERE)
		return (get_angle_sp(scene, Phit[0], num));
	else
		return (-1);
}
