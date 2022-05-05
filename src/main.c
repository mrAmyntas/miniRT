#include "../inc/miniRT.h"

static void	background(t_data *data, t_scene *scene)
{
	int	i;
	int	j;

	data->mlx_img = mlx_new_image(data->mlx, data->width + 10, data->height + 10);
	data->color = create_rgbt(0, 0, 0, 255);
	i = 0;
	while (i < data->width + 1)
	{
		j = 0;
		while (j < data->height + 1)
		{
			mlx_put_pixel(data->mlx_img, i, j, data->color);
			j++;
		}
		i++;
	}
}

void	hook(void *param)
{
	t_data *data;

	data = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

int	main(int argc, char **argv)
{

	t_data	data;
	t_scene	scene;

	data.height = 640;
	data.width = 800;
	if (argc != 2)
		ft_error(1, "Invalid amount of arguments\n");
	read_scene(&scene, argv[1]);
	data.mlx = mlx_init(data.width, data.height, "MLX42", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	background(&data, &scene);	
	plane(&data, &scene);
	//sphere(&data, &scene);
	//cylinder(&data, &scene);
	mlx_image_to_window(data.mlx, data.mlx_img, -1, -1);
	mlx_loop_hook(data.mlx, &hook, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	/*
	data.mlx_img = mlx_new_image(data.mlx, 64, 64);
	memset(data.mlx_img->pixels, 255, data.mlx_img->width * data.mlx_img->height * sizeof(int));
	mlx_image_to_window(data.mlx, data.mlx_img, WIDTH/2-25, HEIGHT/2-25);
	*/
	free(scene.pl);
	free(scene.cy);
	free(scene.sp);
	free(scene.light);
	free(scene.cam);

	//system("leaks miniRT");
	return(EXIT_SUCCESS);
}
