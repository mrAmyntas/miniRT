#include "../inc/miniRT.h"


double	get_sp_angle(t_scene *scene, int num[2], t_vect3d Phit)
{
	double		angle;
	t_ray		ray;
	t_vect3d	N;

    N = normalize_vector(subtract_vectors(Phit, scene->sp[num[1]].C));
	ray.dir = normalize_vector(subtract_vectors(Phit, scene->light->ori));
    ray.eye = scene->light->ori;
    ray.dir = multiply_vector(ray.dir, -1);
    angle = acos(dot_product(N, ray.dir)) / (M_PI / 180);
	return (angle);
}

double	get_pl_angle(t_scene *scene, int num[2], t_vect3d Phit)
{
	double		angle;
	t_vect3d	tmp;

	tmp = normalize_vector(subtract_vectors(scene->light->ori, Phit));
	angle = acos(dot_product(scene->pl[num[1]].orth_vec, tmp)) / (M_PI / 180);
	if (angle > 90)
		angle = 180 - angle;
	return (angle);
}

double	get_angle(t_scene *scene, int num[2], t_vect3d Phit)
{
	double	angle;

	if (num[0] == PLANE)
		angle = get_pl_angle(scene, num, Phit);
	else if (num[0] == SPHERE)
		angle = get_sp_angle(scene, num, Phit);
	else
		angle = 45;
	return (angle);
}

int	get_color(t_scene *scene, int num[2], double t, t_vect3d Phit)
{
	double	angle;
	int		shadow;

	angle = get_angle(scene, num, Phit);
	shadow = 0;
	if (num[0] == PLANE)
		return (calculate_light(angle, Phit, scene->pl[num[1]].hsl, scene, t, shadow));
	else if (num[0] == SPHERE)
		return (calculate_light(angle, Phit, scene->sp[num[1]].hsl, scene, t, shadow));
	else if (num[0] == CYLINDER)
		return (scene->cy[num[1]].rgb);
	return (-1);
}

	// tmp = normalize_vector(subtract_vectors(scene->light->ori, intersect));
	// angle = acos(dot_product(scene->pl[num].orth_vec, tmp)) / (M_PI / 180);
	// if (angle > 90)
	// {
	// 	angle = 180 - angle;
	// }



bool check_if_plane_between_light_and_cam(t_scene *scene, int num[2])
{
	t_ray	ray;
	int		t;
	int		num2;

	ray.eye = scene->cam->eye;
	ray.dir = normalize_vector(subtract_vectors(scene->light->ori, ray.eye));
	t = cast_ray_to_space_check_if_hit_pl(scene, &ray, &num2);
	if (t > 0 && num[1] == num2) // camera -> light hits same plane 
	{
		ray.eye = add_vectors(ray.eye, multiply_vector(ray.dir, t)); //intersect point
		if (distance_two_points(scene->cam->eye, ray.eye) < distance_two_points(scene->cam->eye, scene->light->ori))//from cam -> obj hits first, so light is behind plane
			return (true);
	}
	return (false);
}

double	smallest(double t[3])
{
	if ((t[0] < t[1] || t[1] < 0) && (t[0] < t[2] || t[2] < 0) && t[0] > 0)
		return (t[0]);
	else if ((t[1] < t[2] || t[2] < 0) && t[1] > 0)
		return (t[1]);
	else if (t[2] > 0)
		return (t[2]);
	return (-1);
}

double	find_closest_object(t_scene *scene, t_ray *ray, int num[2])
{
	double	t[4];
	int		i;
	int		numb[3];

	t[0] = cast_ray_to_space_check_if_hit_pl(scene, ray, &numb[0]);
	t[1] = cast_ray_to_space_check_if_hit_cy(scene, ray, &numb[1]);
	numb[2] = find_hit_sphere(scene, *ray, scene->amount[1], &t[2]);
	t[3] = smallest(t);
	if (comp_d(t[0], t[3]))
	{
		num[0] = 0;
		num[1] = numb[0];
	}
	else if (comp_d(t[1], t[3]))
	{
		num[0] = 1;
		num[1] = numb[1];
	}
	else if (comp_d(t[2], t[3]))
	{
		num[0] = 2;
		num[1] = numb[2];
	}
	else
		num[0] = -1;
	return (t[0]);
}


int	find_pixel_color(t_scene *scene, double t, int num[2], t_vect3d Phit)
{
	t_ray		ray;
	int			num2[2];
	t_vect3d	Phit2;
	double		t2;
	//check if light -> obj hits the same obj
	ray.eye = scene->light->ori;
	ray.dir = normalize_vector(subtract_vectors(Phit, ray.eye));
	t2 = find_closest_object(scene, &ray, num);
	Phit2 = add_vectors(ray.eye, multiply_vector(ray.dir, t2));
	if (num2[0] == num[0] && num2[1] == num2[1] && compare_vectors(Phit, Phit2)) //light hits same obj as the camera ray at the same point
	{
		//cast ray from camera to light, if this hits obj, check if it was BEFORE light, if it isnt, the light is hitting the BACK of the obj (only really matters for plane)
		if (num[0] == 0 && check_if_plane_between_light_and_cam(scene, num)) // true means plane blocks light of itself
			return (-1);
		else
		{
 			//calculate_light(double angle, t_vect3d Phit, t_vect3d hsl, t_scene *scene, double t, int shadow)
			//use the type+type_num (num[0] num[1] and distance (t2) to determine angle and calc color)
			return (get_color(scene, num, t2, Phit));
		}
	}
	// not lit
	return (-1);
}

void	charge_my_lasers(t_data *data, t_scene *scene, int x, int y)
{
	t_ray		ray;
	double		t;
	int			num[2]; //num[0] is type: 0=pl, 1=cy, 2 = sp    num[1] = number of that type that has been hit by ray
	int			color;
	t_vect3d	Phit;

	ray = get_ray(scene, data, x, y);
	t = find_closest_object(scene, &ray, num);
	if (t != -1)
	{
		Phit = add_vectors(ray.eye, multiply_vector(ray.dir, t));
		color = find_pixel_color(scene, t, num, Phit);
		if (color != -1)
			mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), color);
	}
	//mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), scene->pl[0].rgb);
}

void	positions_my_lasers(t_data *data, t_scene *scene)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width + 1)
	{
		y = 0;
		while (y < data->height + 1)
		{
			charge_my_lasers(data, scene, x, y);
			y++;
		}
		x++;
	}
}
