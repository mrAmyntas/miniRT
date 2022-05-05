#include "../inc/miniRT.h"


double	cast_ray_to_space_check_if_hit_cy(t_scene *scene, t_ray *ray, int num)
{
	double	a;
	double	b;
	double	c;
	double	t[2];
	double	D;
	double r;
	double zz[2];
	double z_min;
	double z_max;
	// t_vect3d x;
	// t_vect3d z;
	// t_vect3d y;
	// t_vect3d d;

	// x = normalize_vector(cross_product(scene->cy->dir, ray->dir));
	// z = scene->cy->dir;
	// y = normalize_vector(cross_product(z, x));
	// d = multiply_vector(x, dot_product(subtract_vectors(scene->cam->eye, scene->cy->eye), x));


// r = sqrt ( x ^2 + y ^2 )
// r ^2 = x^2 + y^2
// r = diameter/2
// (d/2)^2 = x^2 + y^2
// z1 = zE + t1zD and z2 = zE + t2zD

	r = pow((scene->cy[num].diameter / 2), 2);
	a = (pow(ray->dir.x, 2) + pow(ray->dir.y, 2));
	b = (2 * ray->eye.x * ray->dir.x) + (2 * ray->eye.y * ray->dir.y);
	c = pow(ray->eye.x, 2) + pow(ray->eye.y, 2) - r;
	D = pow(b, 2) - (4 * a * c);
	if (D < 0)
		return (-1);
	t[0] = (-b - sqrt(D)) / (2 * a);
	t[1] = (-b + sqrt(D)) / (2 * a);
	zz[0] = ray->eye.z + ray->dir.z * t[0]; 
	zz[1] = ray->eye.z + ray->dir.z * t[1];
	z_min = 0;
	z_max = scene->cy[num].height;

	if ((z_min < zz[0] && zz[0] < z_max) || (z_min < zz[1] && zz[1] < z_max))
		printf("t0:%f t1:%f zz0:%f zz1:%f\n", t[0], t[1], zz[0], zz[1]);
	// if (t[0] < t[1])
	// {
	// 	ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[0]));
	// 	return (t[0]);
	// }
	// ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[1]));
	// return (t[1]);
	if (t[0] < t[1] && z_min < zz[0] && zz[0] < z_max && t[0] >= 0)
	{
		ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[0]));
		return (t[0]);
	}
	else if (z_min < zz[1] && zz[1] < z_max && t[1] >= 0)
	{
		ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[1]));
		return (t[1]);
	}
	return (-1);
}


//
// Cylindrical polar to rectangular
//
//	x^2 + y^2 = 1, z_min < z < z_max  (r = 1, z_min < z < z_max)
//
// x	=	r cos 0
// y	=	r sin 0
// z	=	z	

// r	=	sqrt{x^2+y^2}
// 0	=	tan^-1 * y/x
// z	=	z


void calc_hit2(t_data *data, t_scene *scene, double x, double y, int num)
{
	t_ray		ray;
	t_ray		intersect;
	double		tmp;
	double		tmp2;

	ray = get_ray(scene, data, x, y);
	//printf("ray: e: %f %f %f  d: (%f,%f,%f)\n", ray.eye.x, ray.eye.y, ray.eye.z, ray.dir.x, ray.dir.y, ray.dir.z);
	tmp = cast_ray_to_space_check_if_hit_cy(scene, &ray, num);
	//printf("tmp:%f\n", tmp);
	if (tmp != -1) // = hit  (ray is now intersect point)
	{
		intersect.eye = ray.eye;
		//check if light -> intersect point hits the same intersect
		ray.eye = scene->light->ori;
		ray.dir = normalize_vector(subtract_vectors(intersect.eye, scene->light->ori));
		tmp2 = cast_ray_to_space_check_if_hit_cy(scene, &ray, num); // ray.eye is new intersect
		if (compare_vectors(ray.eye, intersect.eye)) // is lit
			mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), light_the_pixel_cy(scene, intersect, num));
		else
			mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), add_shade(0.8, data->color));
		return ;
	}
	//mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), add_shade(0.9, data->color));
	//printf("check\n");

}

void	draw_cylinder(t_data *data, t_scene *scene, int num)
{
	int	i;
	int	j;

	data->color = scene->cy[0].rgb;
	i = 0;
	while (i < data->width + 1)
	{
		j = 0;
		while (j < data->height + 1)
		{
			calc_hit2(data, scene, i, j, num);
			j++;
		}
		i++;
	}
}

int	cylinder(t_data *data, t_scene *scene)
{
	int	i;

	data->mlx_img = mlx_new_image(data->mlx, data->width + 10, data->height + 10);
	i = 0;
	while (i < scene->amount[2])
	{
		draw_cylinder(data, scene, i);
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, -1, -1);
	return 0;
}


int	light_the_pixel_cy(t_scene *scene, t_ray intersect, int num)
{
	t_vect3d	tmp;
	double		angle;
	double		distance;
	double		bright;
	int			rgb;

    bright = scene->light->brightness + 0.2;
	if (bright > 1)
		bright = 1;
	return (hsl_to_rgb(scene->sp->hsl));
}
