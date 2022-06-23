#include "../inc/miniRT.h"

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
	t[4] = find_hit_torus(scene, ray, &numb[4], cap);
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

bool	checkers(t_scene *scene, t_vect3d Phit, int num)
{
	double 		u;
	double 		v;

	Phit = subtract_vectors(Phit, scene->sp[num].C);
	u = 1 - (atan2(Phit.x, Phit.z) / (2 * M_PI) + 0.5);
	v = 1 - (acos(Phit.y / (scene->sp[num].size / 2)) / M_PI);
	if (!(((int)(u * scene->checker[1]) + (int)(v * scene->checker[0])) % 2))
		return (false);
	else
		return (true);
}

bool	checkers2(t_scene *scene, t_vect3d Phit, int num)
{
	double 		u;
	double 		v;
	t_vect3d	test[3];

	test[0].x = 0;
	test[0].y = 1;
	test[0].z = 0;
	Phit = subtract_vectors(Phit, scene->cy[num].eye);
	test[1] = multiply_vector(test[0], sqrt(fabs(pow(magnitude(Phit), 2) - pow(scene->cy[num].r, 2))));
	test[2] = multiply_vector(scene->cy[num].dir, sqrt(fabs(pow(magnitude(Phit), 2) - pow(scene->cy[num].r, 2))));
	Phit = add_vectors(Phit, subtract_vectors(test[1], test[2]));
	printf("%i:	%f %f %f\n", num, Phit.x, Phit.y, Phit.z);
	u = 1 - (atan2(Phit.x, Phit.z) / (2 * M_PI) + 0.5);
	v = Phit.y;// * (scene->cy[num].r * 2);
	if (!(((int)(u * scene->checker[1]) + (int)(v * scene->checker[0])) % 2))
		return (false);
	else
		return (true);
}

// sets the ray from Phit to light
// and returns the colour of the  pixel with the right lumination
int	get_color(t_scene *scene, int num[2], t_vect3d Phit[2])
{
	scene->i = 0;
	while (scene->i < scene->amount[LIGHT])
	{
		calc_light_strength(scene, Phit, num);
		scene->i++;
	}
	if (num[0] == SPHERE)
	{
		if (!checkers(scene, Phit[0], num[1]))
			return (calculate_light(scene->sp[num[1]].lsh, scene));
	}
	if (num[0] == CYLINDER)
	{
		if (!checkers2(scene, Phit[0], num[1]))
			return (calculate_light(scene->cy[num[1]].lsh, scene));
	}
	//if (num[0] == PLANE)
	//{
	//	if (Phit[0].x <= 0 && ((!(((int)Phit[0].x / scene->checker[1]) % 2) && (((int)Phit[0].z / scene->checker[0]) % 2)) || ((((int)Phit[0].x / scene->checker[1]) % 2) && !(((int)Phit[0].z / scene->checker[0]) % 2))))
	//		return (calculate_light(scene->pl[num[1]].lsh, scene));
	//	if (Phit[0].x > 0 && (((((int)Phit[0].x / scene->checker[1]) % 2) && (((int)Phit[0].z / scene->checker[0]) % 2)) || (!(((int)Phit[0].x / scene->checker[1]) % 2) && !(((int)Phit[0].z / scene->checker[0]) % 2))))
	//		return (calculate_light(scene->pl[num[1]].lsh, scene));
	//}
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
