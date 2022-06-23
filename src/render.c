#include "../inc/miniRT.h"

// finds the closest object and sets num to the id of the object
//num[0] is type of object
//num[1] the number of the specific objecy (e.g. plane #3)
double	find_closest_object(t_scene *scene, t_ray *ray, int num[2], int set)
{
	double	t[5];
	int		i;
	int		numb[5];

	t[0] = find_hit_pl(scene, ray, &numb[0], set);
	t[1] = find_hit_cy(scene, ray, &numb[1], set);
	t[2] = find_hit_sphere(scene, ray, &numb[2], set);
	t[3] = find_hit_disc(scene, ray, &numb[3]);
	t[4] = find_hit_torus(scene, ray, &numb[4], set);
	i = find_smallest(t, 1, 5);
	if (i != -1)
	{
		num[0] = i;
		num[1] = numb[i];
		return (t[i]);
	}
	return (-1);
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
	x.angle = get_angle(scene, num, Phit[1], &x.n);
	if ((inside_object(scene, Phit, num) && x.angle < 90.0 && x.angle != -1))
		return ;
	else if ((!inside_object(scene, Phit, num) && x.angle > 90.0) || (x.angle == -1 && !(inside_object(scene, Phit, num) && x.angle < 90.0)))
		return ;
	if (inside_object(scene, Phit, num) && (x.angle > 90.0 || x.angle == -1))
	{
		x.n = multiply_vector(x.n, -1);
		x.angle = 180 - x.angle;
	}
	x.r = subtract_vectors(multiply_vector(x.n, 2
				* dot_product(x.n, x.ray.dir)), x.ray.dir);
	x.specular = pow(dot_product(multiply_vector(
					scene->ray_cam.dir, -1), x.r), 50);
	x.specular *= scene->light[scene->i].Ks;
	x.diffuse = (((100 - x.t) / 100 + (90 - x.angle)
				/ 90) / 2) * scene->light[scene->i].Kd;
	scene->light[scene->i].strength = x.specular + x.diffuse;
	if (scene->light[scene->i].strength < 0)
		scene->light[scene->i].strength = 0;
	if (scene->light[scene->i].strength > 1)
		scene->light[scene->i].strength = 1;
	x.ray.eye = Phit[0];
	x.ray.dir = normalize_vector(subtract_vectors(
				scene->light[scene->i].ori, x.ray.eye));
	x.ray.eye = add_vectors(x.ray.eye, multiply_vector(x.n, 0.000001));
	scene->light[scene->i].strength *= check_shadows(x.ray, scene, x.t, Phit);
}

t_vect3d	get_hsl(t_scene *scene, int *num)
{
	t_vect3d	hsl;

	if (num[0] == PLANE && scene->pl[num[1]].checker == 0)
		hsl = scene->pl[num[1]].hsl;
	else if (num[0] == PLANE)
		hsl = scene->pl[num[1]].lsh;
	else if (num[0] == SPHERE && scene->sp[num[1]].checker == 0)
		hsl = scene->sp[num[1]].hsl;
	else if (num[0] == SPHERE)
		hsl = scene->sp[num[1]].lsh;
	else if (num[0] == CYLINDER && scene->cy[num[1]].checker == 0)
		hsl = scene->cy[num[1]].hsl;
	else if (num[0] == CYLINDER)
		hsl = scene->cy[num[1]].lsh;	
	else if (num[0] == DISC && scene->di[num[1]].checker == 0)
		hsl = scene->di[num[1]].hsl;
	else if (num[0] == DISC)
		hsl = scene->di[num[1]].lsh;	
	else if (num[0] == TORUS && scene->tor[num[1]].checker == 0)
		hsl = scene->tor[num[1]].hsl;
	else if (num[0] == TORUS)
		hsl = scene->tor[num[1]].lsh;
	return (hsl);
}

//returns the colour of the  pixel with the right lumination
int	get_color(t_scene *scene, int num[2], t_vect3d Phit[2])
{
	t_vect3d	hsl;

	scene->i = 0;
	while (scene->i < scene->amount[LIGHT])
	{
		calc_light_strength(scene, Phit, num);
		scene->i++;
	}
	hsl = get_hsl(scene, num);
	return (calculate_light(hsl, scene));
}

//gets the ray from cam to pixel, 
//finds the closest hit to an object and sets its colour.
//num[0] is type: 0=pl, 1=cy, 2 = sp
//num[1] = number of that type that has been hit by ray
void	set_pixel(t_data *data, t_scene *scene, int x, int y)
{
	double		t;
	int			num[2];
	int			color;
	t_vect3d	phit[2];

	scene->ray_cam = get_ray(scene, x, y);
	t = find_closest_object(scene, &scene->ray_cam, num, 1);
	if (t > 0)
	{
		phit[0] = add_vectors(scene->ray_cam.eye,
				multiply_vector(scene->ray_cam.dir, t));
		color = get_color(scene, num, phit);
		if (isnan(color))
			color = 0xFFFFFFFF;
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
