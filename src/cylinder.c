#include "../inc/miniRT.h"
// diffuse component (Lambert’s Law)
// Specular Component (phong)
//	Ambient Term 

t_matrix44d	matrix_to_translate_to_xyx(t_vect3d C)
{
	t_matrix44d model;

	model.row1.x = 1;
	model.row1.y = 0;
	model.row1.z = 0;
	model.row1.t = C.x;
	model.row2.x = 0;
	model.row2.y = 1;
	model.row2.z = 0;
	model.row2.t = C.y;
	model.row3.x = 0;
	model.row3.y = 0;
	model.row3.z = 1;
	model.row3.t = C.z;
	model.row4.x = 0;
	model.row4.y = 0;
	model.row4.z = 0;
	model.row4.t = 1;
	return (model);
}

double	cast_ray_to_space_check_if_hit_cy(t_scene *scene, t_ray *ray, int num)
{
	double	a;
	double	b;
	double	c;
	double	t[4] = {0, 0, 0 ,0};
	double	D;
	double r;
	double zz[2];
	double z_min;
	double z_max;
	static int i = 0;

	if (i == 0)
	{
		t_matrix44d Translation_Matrix = matrix_to_translate_to_xyx(scene->cy[num].eye);
		t_vec4d		origin_p = {0, 0, 0, 1};
		t_vec4d		transform_p = matrix44d_x_vert4d(Translation_Matrix, origin_p);
		printf_vect4d(transform_p);
		i++;
	}

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

	

	//if ((z_min < zz[0] && zz[0] < z_max) || (z_min < zz[1] && zz[1] < z_max))
	//	printf("t0:%f t1:%f zz0:%f zz1:%f\n", t[0], t[1], zz[0], zz[1]);
	if (t[0] < t[1] && z_min < zz[0] && zz[0] < z_max && t[0] >= 0)
	{
		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
		{
			t[2] = (z_min - ray->eye.z) / ray->dir.z;
			if (t[2] < t[0] && t[2] > 0)
			{
				ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[2]));
				return t[2];
			}
		}
		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
		{
			t[3] = (z_max - ray->eye.z) / ray->dir.z;
			if (t[3] < t[0] && t[3] > 0)
			{
				ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[3]));
				return t[3];
			}
		}
		ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[0]));
		return (t[0]);
	}
	else if (z_min < zz[1] && zz[1] < z_max && t[1] >= 0)
	{
		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
		{
			t[2] = (z_min - ray->eye.z) / ray->dir.z;
			if (t[2] < t[1] && t[2] > 0)
			{
				ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[2]));
				return t[2];
			}
		}
		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
		{
			t[3] = (z_max - ray->eye.z) / ray->dir.z;
			if (t[3] < t[1] && t[3] > 0)
			{
				ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[3]));
				return t[3];
			}
		}
		ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[1]));
		return (t[1]);
	}
	return (-1);
}


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

	ray = get_ray(scene, data, x, y); //camera pov ray to pixel
	tmp = cast_ray_to_space_check_if_hit_cy(scene, &ray, num);
	if (tmp != -1) // = hit  (ray is now intersect point)
	{
		intersect.eye = ray.eye;
		//check if light -> intersect point hits the same intersect
		ray.eye = scene->light->ori;
		ray.dir = normalize_vector(subtract_vectors(intersect.eye, scene->light->ori));
		tmp2 = cast_ray_to_space_check_if_hit_cy(scene, &ray, num); // ray.eye is new intersect
	//	printf("ray: %f %f %f    intersect: %f %f %f\n", ray.eye.x, ray.eye.y, ray.eye.z, intersect.eye.x, intersect.eye.y, intersect.eye.z);
		if (tmp2 != -1 && compare_vectors(ray.eye, intersect.eye) == true) // is lit
		{
			//printf("ray: %f %f %f    intersect: %f %f %f\n", ray.eye.x, ray.eye.y, ray.eye.z, intersect.eye.x, intersect.eye.y, intersect.eye.z);
			mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), light_the_pixel_cy(scene, intersect, num)); //light_the_pixel_cy(scene, intersect, num)
		}
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

	distance = distance_two_points(scene->light->ori, intersect.eye);
	bright = (scene->light->brightness) - (distance / 20);
    bright = scene->light->brightness + scene->a_ratio;
	if (bright > 1)
		bright = 1;
	scene->cy[num].hsl.z = bright;
	return (hsl_to_rgb(scene->cy[num].hsl));
}
