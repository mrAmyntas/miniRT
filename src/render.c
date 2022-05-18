#include "../inc/miniRT.h"


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

// finds the closest object and sets num to the id of the object
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
		num[0] = PLANE;
		num[1] = numb[0];
	}
	else if (comp_d(t[1], t[3]))
	{
		num[0] = CYLINDER;
		num[1] = numb[1];
	}
	else if (comp_d(t[2], t[3]))
	{
		num[0] = SPHERE;
		num[1] = numb[2];
	}
	else
		num[0] = -1;
	return (t[3]);
}

// checks if the light ray hits Phit and is not blocked by another object
// t = distance from Phit to light
// t2 = distance from Phit to an object on the ray
int	check_shadows(t_ray ray, t_scene *scene, double t)
{
	double		t2;
	int			num[2];
	t_vect3d	Phit;

	t2 = find_closest_object(scene, &ray, num);
	if (comp_d(t, t2) && t2 > 0)
		return (0);
	return (1);
}

// calculates the angle light hits Phit on a sphere
double	get_sp_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		angle;
	t_ray		ray;

    *N = normalize_vector(subtract_vectors(Phit, scene->sp[num[1]].C));
	ray.dir = normalize_vector(subtract_vectors(scene->light->ori, Phit));
    angle = acos(dot_product(*N, ray.dir)) / (M_PI / 180);
	return (angle);
}

// calculates the angle light hits Phit on a plane
double	get_pl_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		angle;
	t_vect3d	tmp;

	tmp = normalize_vector(subtract_vectors(scene->light->ori, Phit));
	angle = acos(dot_product(scene->pl[num[1]].orth_vec, tmp)) / (M_PI / 180);
	*N = scene->pl[num[1]].orth_vec;
	if (angle > 90)
	{
		angle = 180 - angle;
		*N = multiply_vector(*N, -1);
	}
	return (angle);
}

// finds the right function to calculate the angle on Phit
double	get_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double	angle;

	if (num[0] == PLANE)
		angle = get_pl_angle(scene, num, Phit, N);
	else if (num[0] == SPHERE)
		angle = get_sp_angle(scene, num, Phit, N);
	else
		angle = 5;
	return (angle);
}

int	check_if_plane_between_cam_and_light(t_scene *scene, t_vect3d Phit[2], double t, int num[2], double angle)
{
	t_ray	ray;
	int		num2;
	int		num3;
	double	t2[2];

	ray.eye = scene->light->ori;
	ray.dir = normalize_vector(subtract_vectors(Phit[0], ray.eye));
	t2[0] = cast_ray_to_space_check_if_hit_pl(scene, &ray, &num2); //ray from light -> obj
	ray.eye = scene->cam->eye;
	ray.dir = normalize_vector(subtract_vectors(scene->light->ori, ray.eye));
	t2[1] = cast_ray_to_space_check_if_hit_pl(scene, &ray, &num3); //ray from cam -> light
	if (t2[1] > 0 && num2 == num3 && t2[1] < distance_two_points(scene->cam->eye, scene->light->ori))
	{
		if (num[0] == PLANE)
			return (calculate_light2(angle, Phit[0], scene->pl[num[1]].hsl, scene, t, 1));
		if (num[0] == SPHERE)
			return (calculate_light2(angle, Phit[0], scene->sp[num[1]].hsl, scene, t, 1));
		if (num[0] == CYLINDER)
			return (calculate_light2(angle, Phit[0], scene->cy[num[1]].hsl, scene, t, 1));
	}
	return (-1);
}


// sets the ray from Phit to light and returns the colour of the  pixel with the right lumination
int	get_color(t_scene *scene, int num[2], double t, t_vect3d Phit[2])
{
	double		angle;
	int			shadow;
	t_ray		ray;
	t_vect3d	N;

	angle = get_angle(scene, num, Phit[0], &N);
	shadow = check_if_plane_between_cam_and_light(scene, Phit, t, num, angle);
	if (shadow != -1)
		return (shadow);
	ray.eye = Phit[0];
	ray.dir = normalize_vector(subtract_vectors(scene->light->ori, ray.eye)); 
	ray.eye = add_vectors(ray.eye, multiply_vector(N, 0.000001)); // 0.000001 = bias
	shadow = check_shadows(ray, scene, t); //casting ray from the object to the light!
	if (!compare_vectors(Phit[0], Phit[1]))
		shadow = 0;
	if (num[0] == PLANE)
		return (calculate_light(angle, Phit[0], scene->pl[num[1]].hsl, scene, t, shadow));
	else if (num[0] == SPHERE)
		return (calculate_light(angle, Phit[0], scene->sp[num[1]].hsl, scene, t, shadow));
	else if (num[0] == CYLINDER)
		return (calculate_light(angle, Phit[0], scene->cy[num[1]].hsl, scene, t, shadow));
	return (-1);
}

// sets the ray from light to Phit
int	find_pixel_color(t_scene *scene, double t, int num[2], t_vect3d Phit)
{
	t_ray		ray;
	int			num2[2];
	t_vect3d	Phit2[2];
	double		t2;
	
	Phit2[0] = Phit;
	ray.eye = scene->light->ori;
	ray.dir = normalize_vector(subtract_vectors(Phit, ray.eye));
	t2 = find_closest_object(scene, &ray, num2);
	Phit2[1] = add_vectors(ray.eye, multiply_vector(ray.dir, t2));
	return (get_color(scene, num, t2, Phit2));
}

// gets the ray from cam to pixel, finds the closest hit to an object and sets its colour.
// 	num[0] is type: 0=pl, 1=cy, 2 = sp
// 	num[1] = number of that type that has been hit by ray
void	set_pixel(t_data *data, t_scene *scene, int x, int y)
{
	t_ray		ray;
	double		t;
	int			num[2];
	int			color;
	t_vect3d	Phit;

	ray = get_ray(scene, data, x, y);
	t = find_closest_object(scene, &ray, num);
	if (t > 0)
	{
		Phit = add_vectors(ray.eye, multiply_vector(ray.dir, t));
		color = find_pixel_color(scene, t, num, Phit);
		mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), color);
	}
}

// loops through all the pixels in the window
void	loop_pixels(t_data *data, t_scene *scene)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width + 1)
	{
		y = 0;
		while (y < data->height + 1)
		{
			set_pixel(data, scene, x, y);
			y++;
		}
		x++;
	}
}
