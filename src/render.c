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
double	find_closest_object(t_scene *scene, t_ray *ray, int num[2], int cap)
{
	double	t[4];
	int		i;
	int		numb[3];

	t[0] = find_hit_pl(scene, ray, &numb[0]);
	t[1] = find_hit_cy(scene, ray, &numb[1], cap);
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
int	check_shadows(t_ray ray, t_scene *scene, double t, t_vect3d Phit[2])
{
	double		t2;
	int			num[2];

	if (!check_if_plane_between_cam_and_light(scene, Phit) || !compare_vectors(Phit[0], Phit[1]))
		return (0);
	t2 = find_closest_object(scene, &ray, num, 0);
	if (comp_d(t, t2) && t2 > 0)
		return (0);
	return (1);
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
		angle = get_cy_angle(scene, num, Phit, N);
	return (angle);
}

// sets the ray from Phit to light and returns the colour of the  pixel with the right lumination
int	get_color(t_scene *scene, int num[2], double t, t_vect3d Phit[2])
{
	double		angle;
	t_ray		ray;
	t_vect3d	N;

	angle = get_angle(scene, num, Phit[0], &N);
	ray.eye = Phit[0];
	ray.dir = normalize_vector(subtract_vectors(scene->light->ori, ray.eye)); 
	ray.eye = add_vectors(ray.eye, multiply_vector(N, 0.000001)); // 0.000001 = bias
	if (num[0] == PLANE)
		return (calculate_light(angle, scene->pl[num[1]].hsl, scene, t, check_shadows(ray, scene, t, Phit)));
	else if (num[0] == SPHERE)
		return (calculate_light(angle, scene->sp[num[1]].hsl, scene, t, check_shadows(ray, scene, t, Phit)));
	else if (num[0] == CYLINDER)
		return (calculate_light(angle, scene->cy[num[1]].hsl, scene, t, check_shadows(ray, scene, t, Phit)));
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
	t2 = find_closest_object(scene, &ray, num2, 0);
	Phit2[1] = add_vectors(ray.eye, multiply_vector(ray.dir, t2));
	return (get_color(scene, num, t2, Phit2));
}

// gets the ray from cam to pixel, finds the closest hit to an object and sets its colour.
// 	num[0] is type: 0=pl, 1=cy, 2 = sp
// 	num[1] = number of that type that has been hit by ray
void	set_pixel(t_data *data, t_scene *scene, int x, int y)
{
	double		t;
	int			num[2];
	int			color;
	t_vect3d	Phit;

	scene->ray_cam = get_ray(scene, data, x, y);
	t = find_closest_object(scene, &scene->ray_cam, num, 1);
	if (t > 0)
	{
		Phit = add_vectors(scene->ray_cam.eye, multiply_vector(scene->ray_cam.dir, t));
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
