#include "../inc/miniRT.h"


double	cast_ray_to_space_check_if_hit_cy(t_scene *scene, t_ray *ray, int num)
{
	double	a;
	double	b;
	double	c;
	double	t[2];
	double	D;
	a = (pow(ray->dir.x, 2) + pow(ray->dir.y, 2));
	b = 2 * ray->eye.x * ray->dir.x + 2 * ray->eye.y * ray->dir.y;
	c = pow(ray->eye.x, 2) + pow(ray->eye.y, 2) - 1;

	D = pow(b, 2) - 4 * a * c;
	if (D < 0)
		return (-1);
	if (D == 1)
		return (-b / 2 * a);
	t[0] = (-b + D) / 2 * a;
	t[1] = (-b - D) / 2 * a;
	return (t[0] < t[1]); 

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
	t_vect3d	tmp;
	int			color;
	int			angle;
	int			distance;

	color = data->color;
	ray = get_ray(scene, data, x, y);

	if (cast_ray_to_space_check_if_hit_cy(scene, &ray, num)) // = hit -> ray now has intersec coords
	{
	}
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


