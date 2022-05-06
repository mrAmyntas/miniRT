#include "../inc/miniRT.h"

double find_smallest(t_scene *scene, double t[scene->amount[0]])
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i + j < scene->amount[0])
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

//check if in the current direction the camera ray will intersect with the plane[num]
bool	cast_ray_to_space_check_if_hit_pl(t_scene *scene, t_ray *ray, int *num)
{
//	double		t;
	t_vect3d	tmp;	
	double		t[scene->amount[0]];
	int			i;

	//printf("i:%d am:%d\n", i, scene->amount[0]);
	i = 0;
	while (i < scene->amount[0])
	{
		tmp = subtract_vectors(scene->pl[i].coord, ray->eye);
		if (dot_product(scene->pl[i].orth_vec, ray->dir) == 0)
		{ 	//then the ray is parallel to the plane, and there is no intersection point
			t[i] = -1;
			i++;
			continue ;
		}
		t[i] = (dot_product(scene->pl[i].orth_vec, tmp)) / (dot_product(scene->pl[i].orth_vec, ray->dir));
		i++;
	}
	i = find_smallest(scene, t);
	if (i != -1)
	{
		*num = i;
		ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t[i]));
		return (true);
	}
	*num = -1;
	return (false);
	// tmp = subtract_vectors(scene->pl[num].coord, ray->eye);
	// if (dot_product(scene->pl[num].orth_vec, ray->dir) == 0)
	// {
	// 	//then the ray is parallel to the plane, and there is no intersection point
	// 	//printf("parralel\n");
	// 	return (false);
	// }
	// t = (dot_product(scene->pl[num].orth_vec, tmp)) / (dot_product(scene->pl[num].orth_vec, ray->dir));
	// if (t > 0)
	// {
	// 	ray->eye = add_vectors(ray->eye, multiply_vector(ray->dir, t));
	// 	return (true);
	// }
	// return (false);
}

// t_ray	calc_ray(t_data *data, t_scene *scene, double x, double y)
// {
// 	t_ray	ray;

// 	ray.eye.x = (2 * ((x + 0.5) / data->width) - 1) * (data->width / data->height) * tan(scene->c_fov * M_PI / 180 / 2);
// 	ray.eye.y = (1 - 2 * ((y + 0.5) / data->height)) * tan(scene->c_fov * M_PI / 180 / 2);	
// 	ray.eye.z = -1;

// 	ray.dir = normalize_vector(subtract_vectors(ray.eye, scene->origin));
// 	scene->current_dir = normalize_vector(subtract_vectors(ray.eye, scene->origin));
// 	return (ray);
// }

//lights the point
int	light_the_pixel_pl(t_scene *scene, t_ray intersect, int num)
{
	t_vect3d	tmp;
	double		angle;
	double		distance;
	double		bright;
	int			rgb;

	tmp = normalize_vector(subtract_vectors(scene->light->ori, intersect.eye));
	angle = acos(dot_product(scene->pl[num].orth_vec, tmp)) / (M_PI / 180);
	if (angle > 90)
	{
		angle = 180 - angle;
	}
	distance = distance_two_points(scene->light->ori, intersect.eye);
//	bright = 1 / (angle / 1.1) / (distance / 100) * scene->light->brightness / 2;
//	bright = (scene->light->brightness) / (4 * M_PI * (sqrt(distance)));
	bright = (scene->light->brightness) - (distance / 20);
//	bright = bright - (angle/100);
	bright = bright + scene->a_ratio;
	if (bright > 1.0)
		bright = 1.0;
	if (bright <= 0.0)
		bright = 0.01;
	scene->pl[num].hsl.z = bright;
	return (hsl_to_rgb(scene->pl[num].hsl));
}

void calc_hit(t_data *data, t_scene *scene, double x, double y)
{
	t_ray		ray;
	t_ray		intersect;
	int			num;
	int			num2;
	//t_matrix44d	camToWorld;

	//ray = calc_ray(data, scene, x, y); //ray with eye as a pixel point and direction as origin->pixelpoint
	//printf("ray.dir: %f %f %f   ray.eye: %f %f %f     ", ray.dir.x, ray.dir.y, ray.dir.z, ray.eye.x, ray.eye.y, ray.eye.z);
	
	//ray.eye = scene->cam->eye; //sets ray.eye to camera eye, its now 
	//camToWorld = set_camera_to_world(scene->cam->eye, ray.eye);
	//ray.dir = camera_to_world(scene, ray); //camera-to-world translation, sets new direction
	//ray.dir = normalize_vector(ray.dir); //normalize

	ray = get_ray(scene, data, x, y);
	//FIRE MY LASERS
	// cos a = N . L (dot product normal and light vector)
	// a = arccos (n . l)

	if (cast_ray_to_space_check_if_hit_pl(scene, &ray, &num)) // = hit -> ray now has intersec coords , num is which plane
	{
		intersect = ray;
		//printf("ray.eye: %f %f %f\n", ray.eye.x, ray.eye.y, ray.eye.z);
		ray.dir = normalize_vector(subtract_vectors(ray.eye, scene->light->ori));
		ray.eye = scene->light->ori;
		if (cast_ray_to_space_check_if_hit_pl(scene, &ray, &num2) && num2 == num) // light hits SAME plane as well
		{
			//cast ray from camera to light, if this hits plane, check if it was BEFORE light
			ray.eye = scene->cam->eye;
			ray.dir = normalize_vector(subtract_vectors(scene->light->ori, ray.eye));
			if (cast_ray_to_space_check_if_hit_pl(scene, &ray, &num2) && num2 == num) // camera -> light hits plane 
			{
				if (distance_two_points(scene->cam->eye, ray.eye) < distance_two_points(scene->cam->eye, scene->light->ori))//from cam -> obj hits first, so light is behind plane
					mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), add_shade(0.9, scene->pl[num].rgb));
				else
				{
					mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), light_the_pixel_pl(scene, intersect, num));
				}
			}
			else
			{
				mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), light_the_pixel_pl(scene, intersect, num));
			}
		}
		else //light is INSIDE plane or it hits ANOTHER PLANE
		{
			//printf("1\n");
			mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), add_shade(0.9, scene->pl[num].rgb));
		}
	}
}

void	draw_plane(t_data *data, t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->width + 1)
	{
		j = 0;
		while (j < data->height + 1)
		{
			calc_hit(data, scene, i, j);
			j++;
		}
//		printf("\\\\\\\\\\ LOOP FOR X COMPLETE ///////\n");
		i++;
	}
}

int	plane(t_data *data, t_scene *scene)
{
	int	i;

	//data->mlx_img = mlx_new_image(data->mlx, data->width + 10, data->height + 10);
	draw_plane(data, scene);
	//mlx_image_to_window(data->mlx, data->mlx_img, -1, -1);
	return 0;
}



// Orthogonal matrices have a few interesting properties but maybe the most useful one in Computer Graphics, 
// is that the transpose of an orthogonal matrix is equal to its inverse. Assuming Q is an orthogonal matrix, we can write:

// Q^T=Q^-1 which entails that QQ^T=I

	// printf("coords check: cam: [%f,%f,%f]\ncoords check: pl:  [%f,%f,%f]\n", scene->cam->coord.x,scene->cam->coord.y,scene->cam->coord.z, scene->pl[num].coord.x,scene->pl[num].coord.y,scene->pl[num].coord.z);
	// printf("vec check: cam: [%f,%f,%f]\nvec check: pl:  [%f,%f,%f]\n", scene->cam->eye.x,scene->cam->eye.y,scene->cam->eye.z, scene->pl[0].orth_vec.x,scene->pl[0].orth_vec.y,scene->pl[0].orth_vec.z);

	// t_vect3d tmp = {12310, 760, 2};
	// if (is_P_on_plane(scene, tmp, num))
	// 	printf("P is on the plane!\n");
	// if (intersect_eye_plane(scene, &tmp, num))
	// {
	// 	printf("intersect:[%f,%f,%f]\n", tmray.eyep.x, tmray.eye.y, tmp.z);
	// }

//scan left->right depending on fov?
//we have a vector for camera direction (scene->cam->dir)
//with fov of x, what is left most?
//distance between camera and viewport: 𝑑=1/𝑡𝑎𝑛(𝜃𝑓𝑜𝑣/2)) ??? find source pls

//t_vect3d right_edge_fov;
//right_edge_pov = cos(scene->pov)

// PixelNDCx= (Pixelx+0.5) / ImageWidth   NDC = normalized device coordinates
// PixelNDCy= (Pixely+0.5)/ ImageHeight

// PixelScreen x = 2 * PixelNDCx − 1
// PixelScreen y = 1 - 2 * PixelNDCy

//The value now varies from 1 to -1 as Pixely varies from 0 to ImageWidth.
//Coordinates expressed in this manner are said to be defined in screen space.

// PixelCamerax = (2 * PixelScreenx − 1) * aspect_ratio
// PixelCameray = (1 − 2 * PixelScreeny)

// |BC| = tan(α / 2)   BC is line from middle of viewport to top (straight line) alpha is fov.
// 1 rad = 180°/π 
// α(degrees) = α(radians) * 180° / π


// PixelCamerax = (2 * PixelScreenx − 1) * aspect_ratio * tan (fov/2)
// PixelCameray = (1 − 2 * PixelScreeny) * tan (fov/2)

/*
int i = 0;
	int j = 0;

	data->mlx = mlx_init(data->width, data->height, "MLX42", true);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->mlx_img = mlx_new_image(data->mlx, data->width, data->height);
	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));

	data->color = create_rgbt(255, 255, 255, 255);//0xFFFFFF;

	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));
	while (i < data->width)
	{
		j = 0;
		while (j < data->height)
		{
			mlx_put_pixel(data->mlx_img, i, j, data->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, 0, 0);
	data->mlx_img = mlx_new_image(data->mlx, 100, 100);
	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));
	data->color = scene->pl[0].rgb;
	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			mlx_put_pixel(data->mlx_img, i, j, data->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, 10, 10);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);*/



	/*    int i = 0;
	int j = 0;

	data->mlx = mlx_init(data->width, data->height, "MLX42", true);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->mlx_img = mlx_new_image(data->mlx, data->width, data->height);
	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));

	data->color = create_rgbt(255, 255, 255, 255);//0xFFFFFF;

	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));
	while (i < data->width)
	{
		j = 0;
		while (j < data->height)
		{
			mlx_put_pixel(data->mlx_img, i, j, data->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, 0, 0);
	data->mlx_img = mlx_new_image(data->mlx, 100, 100);
	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));
	scene->pl[0].rgb = create_rgbt(255, 0, 0, 255);
	data->color = scene->pl[0].rgb;
	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			mlx_put_pixel(data->mlx_img, i, j, data->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, 10, 10);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);*/


