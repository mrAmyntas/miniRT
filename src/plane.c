#include "../inc/miniRT.h"


void	draw_plane(t_data *data, t_scene *scene, int num)
{
	int aspect_ratio = data->width / data->height;
	int v_pov = aspect_ratio * scene->c_fov;

	
	//scan left->right depending on fov?
	//we have a vector for camera direction (scene->cam->dir)
	//with fov of x, what is left most?
	//distance between camera and viewport: 𝑑=1/𝑡𝑎𝑛(𝜃𝑓𝑜𝑣/2)) ??? find source pls

	double d;

	d = 1/tan(scene->c_fov/2);
	printf("d?: %f\n", d);
	//t_vector right_edge_fov;
	//right_edge_pov = cos(scene->pov)

	// PixelNDCx= (Pixelx+0.5) / ImageWidth   NDC = normalized device coordinates
	// PixelNDCy= (Pixely+0.5)/ ImageHeight

	// PixelScreen x = 2 * PixelNDCx − 1
	// PixelScreen y = 1 - 2 * PixelNDCy

	//The value now varies from 1 to -1 as Pixely varies from 0 to ImageWidth.
	//Coordinates expressed in this manner are said to be defined in screen space.

	// PixelCamerax = (2 * PixelScreenx − 1) * aspect_ratio
	// PixelCameray = (1 − 2 * PixelScreeny)

	// |BC| =tan(α / 2)   BC is line from middle of viewport to top (straight line) alpha is fov.
	// 1 rad = 180°/π 
	// α(degrees) = α(radians) * 180° / π

	double len_viewport = 2 * tan(scene->c_fov * M_PI / 180 / 2);
	printf("len viewport:%f  fov:%f\n", len_viewport, scene->c_fov);




}

int	plane(t_data *data, t_scene *scene, int num)
{

	//printf("coords check: cam: [%f,%f,%f]\ncoords check: pl:  [%f,%f,%f]\n", scene->cam->coord.x,scene->cam->coord.y,scene->cam->coord.z, scene->pl[num].coord.x,scene->pl[num].coord.y,scene->pl[num].coord.z);
	//printf("vec check: cam: [%f,%f,%f]\nvec check: pl:  [%f,%f,%f]\n", scene->cam->vec.x,scene->cam->vec.y,scene->cam->vec.z, scene->pl[num].vec.x,scene->pl[num].vec.y,scene->pl[num].vec.z);

	t_vector tmp = {12310, 760, 2};
	if (is_P_on_plane(scene, tmp, num))
		printf("P is on the plane!\n");
	if (intersect_eye_plane(scene, &tmp, num))
	{
		printf("intersect:[%f,%f,%f]\n", tmp.x, tmp.y, tmp.z);
		draw_plane(data, scene, num);

	}
	return 0;
}

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