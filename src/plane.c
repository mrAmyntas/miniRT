#include "../inc/miniRT.h"

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
void calc_hit(t_data *data, t_scene *scene, double x, double y, int num)
{
	t_ray		ray;
	t_ray		intersect;
	t_vect3d	tmp;
	int			color;
	int			angle;
	int			distance;
	//t_matrix44d	camToWorld;

	//ray = calc_ray(data, scene, x, y); //ray with eye as a pixel point and direction as origin->pixelpoint
	//printf("ray.dir: %f %f %f   ray.eye: %f %f %f     ", ray.dir.x, ray.dir.y, ray.dir.z, ray.eye.x, ray.eye.y, ray.eye.z);
	
	//ray.eye = scene->cam->eye; //sets ray.eye to camera eye, its now 
	//camToWorld = set_camera_to_world(scene->cam->eye, ray.eye);
	//ray.dir = camera_to_world(scene, ray); //camera-to-world translation, sets new direction
	//ray.dir = normalize_vector(ray.dir); //normalize

	color = data->color;
	ray = get_ray(scene, data, x, y);
	//FIRE MY LASERS
	// cos a = N . L (dot product normal and light vector)
	// a = arccos (n . l)



	if (cast_ray_to_space_check_if_hit_pl(scene, &ray, num)) // = hit -> ray now has intersec coords
	{
		//printf("ray.eye: %f %f %f\n", ray.eye.x, ray.eye.y, ray.eye.z);
		ray.dir = normalize_vector(subtract_vectors(ray.eye, scene->light->ori));
		ray.eye = scene->light->ori;
		if (cast_ray_to_space_check_if_hit_pl(scene, &ray, num)) // light hits plane as well
		{
			intersect = ray;
			//cast ray from camera to light, if this hits plane, check if it was BEFORE light
			ray.eye = scene->cam->eye;
			ray.dir = normalize_vector(subtract_vectors(scene->light->ori, ray.eye));
			if (cast_ray_to_space_check_if_hit_pl(scene, &ray, num)) // light hits plane
			{
				if (distance_two_points(scene->cam->eye, ray.eye) < distance_two_points(scene->cam->eye, scene->light->ori))
				{	//from cam -> obj hits first, so light is behind plane
					color = add_shade(0.9, data->color);
					mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), color);
				}
				else
				{
//					printf("eye: %f %f %f  ", ray.eye.x, ray.eye.y, ray.eye.z);
					tmp = normalize_vector(subtract_vectors(scene->light->ori, intersect.eye));
					angle = acos(dot_product(scene->pl->orth_vec, tmp)) / ( M_PI / 180);
					distance = distance_two_points(scene->light->ori, intersect.eye);
					printf("x:%f y:%f angle:%d\n", x, y, angle);
					mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), color);
				}
			}
			else
			{
//					printf("eye: %f %f %f  ", ray.eye.x, ray.eye.y, ray.eye.z);
					tmp = normalize_vector(subtract_vectors(scene->light->ori, intersect.eye));
					angle = acos(dot_product(scene->pl->orth_vec, tmp)) / ( M_PI / 180);
					distance = distance_two_points(scene->light->ori, intersect.eye);
//					printf("x:%f y:%f check:%d\n", x, y, angle);
					mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), color);
			}
		}
		else
		{
			//no light
			color = add_shade(0.9, data->color);
			mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), color);
		}
	}
}

void	draw_plane(t_data *data, t_scene *scene, int num)
{
	int	i;
	int	j;

	data->color = scene->pl[0].rgb;
	i = 0;
	while (i < data->width + 1)
	{
		j = 0;
		while (j < data->height + 1)
		{
			calc_hit(data, scene, i, j, num);
			j++;
		}
		i++;
	}
}

int	plane(t_data *data, t_scene *scene)
{
	int	i;

	data->mlx_img = mlx_new_image(data->mlx, data->width + 10, data->height + 10);
	i = 0;
	while (i < scene->amount[0])
	{
		draw_plane(data, scene, i);
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, -1, -1);
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


