#include "../inc/miniRT.h"
// diffuse component (Lambert’s Law)
// Specular Component (phong)
//	Ambient Term 

void	rotate_ray(t_ray *ray, t_matrix44d I_R)
{
	t_vec4d	new_ray_eye;
	t_vec4d	new_ray_dir;

	new_ray_eye.x = ray->eye.x;
	new_ray_eye.y = ray->eye.y;
	new_ray_eye.z = ray->eye.z;
	new_ray_eye.t = 1;
	new_ray_eye = matrix44d_x_vert4d(I_R, new_ray_eye);
	ray->eye.x = new_ray_eye.x;
	ray->eye.y = new_ray_eye.y;
	ray->eye.z = new_ray_eye.z;
	new_ray_dir.x = ray->dir.x;
	new_ray_dir.y = ray->dir.y;
	new_ray_dir.z = ray->dir.z;
	new_ray_dir.t = 0;
	new_ray_dir = matrix44d_x_vert4d(I_R, new_ray_dir);
	ray->dir.x = new_ray_dir.x;
	ray->dir.y = new_ray_dir.y;
	ray->dir.z = new_ray_dir.z;
	normalize_vector(ray->dir);
}

void	translate_ray(t_vect3d *eye, t_matrix44d I_T)
{
	t_vec4d	new_ray;

	new_ray.x = eye->x;
	new_ray.y = eye->y;
	new_ray.z = eye->z;
	new_ray.t = 1;
	new_ray = matrix44d_x_vert4d(I_T, new_ray);
	eye->x = new_ray.x;
	eye->y = new_ray.y;
	eye->z = new_ray.z;
}

double find_closest_cy(t_scene *scene, t_ray *ray, int *num)
{

	double	a;
	double	b;
	double	c;
	double	t[4] = {-1, -1, -1 ,-1};
	double	D;
	double 	r;
	double 	zz[2];
	double 	z_min;
	double 	z_max;
	int		i;
	double	intersect[scene->amount[2]];
	
	z_min = 0;
	z_max = scene->cy[*num].height;
	t_matrix44d I_T;
	t_matrix44d I_R;
	t_matrix44d T; 

	T = matrix_to_translate_to_xyx(scene->cy[*num].eye);
	I_R = get_inverted_R(scene, *num);
	I_T = get_inverted_T(scene, *num);
	
	// printf_vect3d(ray->dir);
	// printf_vect3d(ray->eye);
	// printf("translation\n");
	translate_ray(&ray->eye, I_T);
	// printf_vect3d(ray->dir);
	// printf_vect3d(ray->eye);
	// printf("rotation\n");
	if (!(scene->cy[*num].dir.x < 0.000001 && scene->cy[*num].dir.y < 0.000001 && fabs(scene->cy[*num].dir.z) > 0.999999))
	{
		rotate_ray(ray, I_R);
	}
	else if (scene->cy[*num].dir.x < 0.000001 && scene->cy[*num].dir.y < 0.000001 && scene->cy[*num].dir.z < -0.999999)
	{
		z_max = scene->cy[*num].height * -1;
	}
	// printf_vect3d(ray->dir);
	// printf_vect3d(ray->eye);
	// printf("\n");

	r = pow((scene->cy[*num].diameter / 2), 2);
	a = (pow(ray->dir.x, 2) + pow(ray->dir.y, 2));
	b = (2 * ray->eye.x * ray->dir.x) + (2 * ray->eye.y * ray->dir.y);
	c = pow(ray->eye.x, 2) + pow(ray->eye.y, 2) - r;
	D = pow(b, 2) - (4 * a * c);
	if (D < 0)
	{
		//printf("NO T's\n");
		return (-1);
	}
	t[0] = (-b - sqrt(D)) / (2 * a);
	t[1] = (-b + sqrt(D)) / (2 * a);
	zz[0] = ray->eye.z + ray->dir.z * t[0]; 
	zz[1] = ray->eye.z + ray->dir.z * t[1];
	//if ((t[0] < t[1] && t[1] - t[0] < 0.001) || (t[1] < t[0] && t[0] - t[1] < 0.001))
	//printf("t0:%f               t1:%f\n", t[0], t[1]);
	if (t[0] > 0 && (t[0] < t[1] || t[1] < 0) && z_min < zz[0] && zz[0] < z_max)
	{
		//printf("t[0]:%f   z0:%f     camera rot: %f %f %f\n", t[0], zz[0], scene->cam->dir.x, scene->cam->dir.y, scene->cam->dir.z);
		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
		{
			t[2] = (z_min - ray->eye.z) / ray->dir.z;
			if (t[2] < t[0] && t[2] > 0)
			{
				//printf("hit t2 (t0>0)\n");
				return t[2];
			}
		}
		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
		{
			t[3] = (z_max - ray->eye.z) / ray->dir.z;
			if (t[3] < t[0] && t[3] > 0)
			{
				//printf("hit t3(t0>0\n");
				return t[3];
			}
		}
		return (t[0]);
	}
	else if (z_min < zz[1] && zz[1] < z_max && t[1] > 0)
	{
		//printf("1\n");
		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
		{
			t[2] = (z_min - ray->eye.z) / ray->dir.z;
			if (t[2] < t[1] && t[2] > 0)
			{
				//printf("hit t2 (t1>0): %f %f %f\n", ray->eye.x, ray->eye.y, ray->eye.z);
				return t[2];
			}
		}
		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
		{
			t[3] = (z_max - ray->eye.z) / ray->dir.z;
			if (t[3] < t[1] && t[3] > 0)
			{
				//printf("hit t3 (t1>0)\n");
				return t[3];
			}
		}
		return (t[1]);
	}
	else //outside of z-values
	{
		t[2] = -1;
		t[3] = -1;
		if ((zz[0] < z_min && zz[1] > z_min) || (zz[1] < z_min && zz[0] > z_min)) // hits cap
			t[2] = (z_min - ray->eye.z) / ray->dir.z;
		if ((zz[0] < z_max && zz[1] > z_max) || (zz[1] < z_max && zz[0] > z_max)) // hits cap
			t[3] = (z_max - ray->eye.z) / ray->dir.z;
		if (t[2] > 0 && (t[2] < t[3] || t[3] < 0))
		{
			printf("2\n");
			return t[2];
		}
		else if (t[3] > 0)
		{
			printf("3\n");
			return t[3];
		}
	}
	return (-1);

}

double find_smallest2(t_scene *scene, double t[scene->amount[2]])
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i + j < scene->amount[2])
	{
		if (t[i + j] > 0 && (t[i + j] < t[i] || t[i] < 0))
		{
			i = i + j;
			j = 1;
		}
		else
			j++;
	}
	if (t[i] > 0)
		return (i);
	return (-1);
}


double	cast_ray_to_space_check_if_hit_cy(t_scene *scene, t_ray *ray, int *num)
{
	double 	t[scene->amount[2]];
	t_ray	new_ray;

	new_ray = *ray;
	*num = 0;
	while (*num < scene->amount[2])
	{
		t[*num] = find_closest_cy(scene, &new_ray, num);
		*num = *num + 1;
	}
	if (*num == 0)
		return (-1);
	*num = find_smallest2(scene, t);
	if (*num == -1)
		return (-1);
	return (t[*num]);
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


void calc_hit2(t_data *data, t_scene *scene, double x, double y)
{
	t_ray		ray;
	t_vect3d	intersect;
	double		tmp;
	double		tmp2;
	static int	i = 0;
	int			num;

	ray = get_ray(scene, data, x, y); //camera pov ray to pixel

	t_matrix44d I_T;
	t_matrix44d I_R;
	t_matrix44d T = matrix_to_translate_to_xyx(scene->cy[num].eye);

	I_R = get_inverted_R(scene, num);
	I_T = get_inverted_T(scene, num);
	// translate_ray(&ray.eye, I_T);
	// if (!(scene->cy[num].dir.x < 0.000001 && scene->cy[num].dir.y < 0.000001 && scene->cy[num].dir.z > 0.999999))
	// 	rotate_ray(&ray, I_R);
	tmp = cast_ray_to_space_check_if_hit_cy(scene, &ray, &num);
//	printf("tmp:%f\n", tmp);
	if (tmp != -1) // = hit  
	{
		intersect = add_vectors(ray.eye, multiply_vector(ray.dir, tmp));
		//check if light -> intersect point hits the same intersect
		//translate_ray(&intersect, T);
		ray.eye = scene->light->ori;
		ray.dir = normalize_vector(subtract_vectors(intersect, scene->light->ori));
		//translate_ray(&ray.eye, I_T);
		if (!(scene->cy[num].dir.x < 0.000001 && scene->cy[num].dir.y < 0.000001 && scene->cy[num].dir.z > 0.999999))
			rotate_ray(&ray, I_R);
		//tmp2 = cast_ray_to_space_check_if_hit_cy(scene, &ray, &num);
		ray.eye = add_vectors(ray.eye, multiply_vector(ray.dir, tmp2));
		//translate_ray(&ray.eye, T);
		if (tmp2 != -1 && compare_vectors(ray.eye, intersect) == true) // is lit
			mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), scene->cy[num].rgb); //light_the_pixel_cy(scene, intersect, num)
		else if (tmp2)
			mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), scene->cy[num].rgb);
		return ;
	}
}

void	draw_cylinder(t_data *data, t_scene *scene)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width + 1)
	{
		y = 0;
		while (y < data->height + 1)
		{
			calc_hit2(data, scene, x, y);
			y++;
		}
		x++;
	}
}

int	cylinder(t_data *data, t_scene *scene)
{
	draw_cylinder(data, scene);
	return 0;
}


int	light_the_pixel_cy(t_scene *scene, t_vect3d intersect, int num)
{
	t_vect3d	tmp;
	double		angle;
	double		distance;
	double		bright;
	int			rgb;

	distance = distance_two_points(scene->light->ori, intersect);
	bright = (scene->light->brightness) - (distance / 20);
    bright = scene->light->brightness + scene->a_ratio;
	if (bright > 1)
		bright = 1;
	scene->cy[num].hsl.z = bright;
	return (hsl_to_rgb(scene->cy[num].hsl));
}














// double	cast_ray_to_space_check_if_hit_cy2(t_scene *scene, t_ray *ray, int num)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	t[4] = {0, 0, 0 ,0};
// 	double	D;
// 	double	r;
// 	double 	zz[2] = {-1, -1};
// 	double 	z_min;
// 	double 	z_max;
// 	int		state;

// 	r = pow((scene->cy[num].diameter / 2), 2);
// 	a = (pow(ray->dir.x, 2) + pow(ray->dir.y, 2));
// 	b = (2 * ray->eye.x * ray->dir.x) + (2 * ray->eye.y * ray->dir.y);
// 	c = pow(ray->eye.x, 2) + pow(ray->eye.y, 2) - r;
// 	D = pow(b, 2) - (4 * a * c);
// 	if (D < 0)
// 		return (-1);
// 	t[0] = (-b - sqrt(D)) / (2 * a);
// 	t[1] = (-b + sqrt(D)) / (2 * a);
// 	zz[0] = ray->eye.z + ray->dir.z * t[0]; 
// 	zz[1] = ray->eye.z + ray->dir.z * t[1];
// 	z_min = 0;
// 	z_max = scene->cy[num].height;

// 	if (t[0] > 0 && t[1] < 0)
// 		state = 1;
// 	if (t[0] < 0 && t[1] > 0)
// 		state = 2;
// 	if (t[0] > 0 && t[1] > 0)
// 		state = 3;

// 	if (state == 1)
// 	{
// 		if (zz[0] > z_min && zz[0] < z_max)
// 			return t[0];
// 	}
// 	if (state == 2)
// 	{
// 		if (zz[1] > z_min && zz[1] < z_max)
// 			return t[1];
// 	}
// 	if (state == 3)
// 	{
// 		if (zz[1] > z_min && zz[1] < z_max && zz[0] > z_min && zz[0] < z_max)
// 		{
// 			if (t[1] < t[0])
// 				return t[1];
// 			return t[0];
// 		}
// 		else if (zz[1] > z_min && zz[1] < z_max)
// 		{
// 			return t[1];
// 		}
// 		else if (zz[0] > z_min && zz[0] < z_max)
// 		{
// 			return t[0];
// 		}
// 		else
// 			return -1;
// 	}
// 	return -1;
// }
