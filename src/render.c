#include "../inc/miniRT.h"

bool	inside_object(t_scene *scene, t_vect3d *Phit, int *num)
{
	double	angle;

	angle = get_camray_angle(scene, Phit, num);
	if (angle > 90 || isnan(angle))
		return (true);
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

// finds the closest object and sets num to the id of the object
double	find_closest_object(t_scene *scene, t_ray *ray, int num[2], int cap)
{
	double	t[5];
	int		i;
	int		numb[5];

	t[0] = find_hit_pl(scene, ray, &numb[0]);
	t[1] = find_hit_cy(scene, ray, &numb[1], cap);
	numb[2] = find_hit_sphere(scene, ray, scene->amount[SPHERE], &t[2]);
	t[3] = find_hit_disc(scene, ray, &numb[3]);
	t[4] = find_hit_torus(scene, ray, &numb[4]);
	i = find_smallest(scene, t, 1, 5);
	if (i != -1)
	{
		num[0] = i;
		num[1] = numb[i];
		return (t[i]);
	}
	return (-1);
}

// checks if the light ray hits Phit and is not blocked by another object
// t = distance from Phit to light
// t2 = distance from Phit to an object on the ray
int	check_shadows(t_ray ray, t_scene *scene, double t, t_vect3d Phit[2])
{
	double		t2;
	int			num[2];

	if (!check_if_plane_between_cam_and_light(scene, Phit)
		|| !compare_vectors(Phit[0], Phit[1]))
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
	else if (num[0] == CYLINDER)
		angle = get_cy_angle(scene, num, Phit, N);
	else if (num[0] == DISC)
		angle = get_di_angle(scene, num, Phit, N);
	else if (num[0] == TORUS)
		angle = get_tor_angle(scene, num, Phit, N);
	if (isnan(angle))
		angle = -1;
	return (angle);
}

void	calc_light_strength(t_scene *scene, t_vect3d Phit[2], int num[2])
{
	t_variable	x;
	int			num2[2];

	scene->light[scene->i].strength = 0;
	x.ray.eye = scene->light[scene->i].ori;
	x.ray.dir = normalize_vector(subtract_vectors(Phit[0], x.ray.eye));
	x.t = find_closest_object(scene, &x.ray, num2, 0);
	Phit[1] = add_vectors(x.ray.eye, multiply_vector(x.ray.dir, x.t));
	x.angle = get_angle(scene, num, Phit[0], &x.N);
	if ((inside_object(scene, Phit, num) && x.angle < 90.0 && x.angle != -1))
		return ;
	else if ((!inside_object(scene, Phit, num) && x.angle > 90.0) || (x.angle == -1 && !(inside_object(scene, Phit, num) && x.angle < 90.0)))
		return ;
	if (inside_object(scene, Phit, num) && x.angle > 90)
		x.angle = 180 - x.angle;
	x.R = subtract_vectors(multiply_vector(x.N, 2
				* dot_product(x.N, x.ray.dir)), x.ray.dir);
	x.specular = pow(dot_product(multiply_vector(
					scene->ray_cam.dir, -1), x.R), 10);
	x.specular *= scene->light[scene->i].Ks;
	x.diffuse = (((100 - x.t) / 100 + (90 - x.angle)
				/ 90) / 2) * scene->light[scene->i].Kd;
	scene->light[scene->i].strength = x.specular + x.diffuse;
	if (scene->light[scene->i].strength < 0)
		scene->light[scene->i].strength = 0;
	x.ray.eye = Phit[0];
	x.ray.dir = normalize_vector(subtract_vectors(
				scene->light[scene->i].ori, x.ray.eye));
	x.ray.eye = add_vectors(x.ray.eye, multiply_vector(x.N, 0.000001));
	scene->light[scene->i].strength *= check_shadows(x.ray, scene, x.t, Phit);
}

// sets the ray from Phit to light
// and returns the colour of the  pixel with the right lumination
int	get_color(t_scene *scene, int num[2], double t, t_vect3d Phit[2])
{
	scene->i = 0;
	while (scene->i < scene->amount[LIGHT])
	{
		calc_light_strength(scene, Phit, num);
		scene->i++;
	}
	// voor checkerboard in een sphere, maar is nog een beetje kijken hoe we het willen
	// if (num[0] == 2 && !((int)Phit[0].x / ((int)scene->sp[num[1]].size / 4) % 2) && !((int)Phit[0].y / ((int)scene->sp[num[1]].size / 4) % 2))
	// 	return(0x000000FF - calculate_light(scene->sp[num[1]].hsl, scene));
	// if (num[0] == 2 && ((int)Phit[0].x / ((int)scene->sp[num[1]].size / 4) % 2) && ((int)Phit[0].y / ((int)scene->sp[num[1]].size / 4) % 2))
	// 	return(0x000000FF - calculate_light(scene->sp[num[1]].hsl, scene));
	if (num[0] == PLANE)
		return (calculate_light(scene->pl[num[1]].hsl, scene));
	else if (num[0] == SPHERE)
		return (calculate_light(scene->sp[num[1]].hsl, scene));
	else if (num[0] == CYLINDER)
		return (calculate_light(scene->cy[num[1]].hsl, scene));
	else if (num[0] == DISC)
		return (calculate_light(scene->di[num[1]].hsl, scene));
	else if (num[0] == TORUS)
		return (calculate_light(scene->tor[num[1]].hsl, scene));
	return (-1);
}

// gets the ray from cam to pixel, 
// finds the closest hit to an object and sets its colour.
// 	num[0] is type: 0=pl, 1=cy, 2 = sp
// 	num[1] = number of that type that has been hit by ray
void	set_pixel(t_data *data, t_scene *scene, int x, int y)
{
	double		t;
	int			num[2];
	int			color;
	t_vect3d	phit[2];

	scene->ray_cam = get_ray(scene, data, x, y);
	t = find_closest_object(scene, &scene->ray_cam, num, 1);
	if (t > 0)
	{
		phit[0] = add_vectors(scene->ray_cam.eye,
				multiply_vector(scene->ray_cam.dir, t));
		color = get_color(scene, num, t, phit);
		mlx_put_pixel(data->mlx_img, (data->width - x),
			(data->height - y), color);
	}

}

// loops through all the pixels in the window
void	loop_pixels(t_data *data, t_scene *scene)
{
	int	x;
	int	y;

	x = 1;
	while (x < data->width + 1)
	{
		y = 1;
		while (y < data->height + 1)
		{
			set_pixel(data, scene, x, y);
			y++;
		}
		x++;
	}
}
