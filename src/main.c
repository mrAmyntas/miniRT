#include "../inc/miniRT.h"

void	hook(void *param)
{
	t_data *data = param;
	int		x_mouse_pos;
	int		y_mouse_pos;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->mlx_img->instances[0].y -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->mlx_img->instances[0].y += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->mlx_img->instances[0].x -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->mlx_img->instances[0].x += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_P)) // cursor position in terminal
	{
		mlx_get_mouse_pos(data->mlx, &x_mouse_pos, &y_mouse_pos);
		printf("mouse x:%d mouse y:%d\n", x_mouse_pos, y_mouse_pos);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_M))
		mlx_set_mouse_pos(data->mlx, data->width/2-25, data->height/2-25); //cursor to center with M
}

int	main(int argc, char **argv)
{

	t_data	data;
	t_scene	scene;

	data.height = 720;
	data.width = 1080;
	if (argc != 2)
		ft_error(1, "Invalid amount of arguments\n");
	read_scene(&scene, argv[1]);
	data.mlx = mlx_init(data.width, data.height, "MLX42", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.mlx_img = mlx_new_image(data.mlx, data.width, data.height);
	plane(&data, &scene);
	globe(&data, &scene);


	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);

	// free stuff
	free(scene.pl);
	free(scene.cy);
	free(scene.sp);
	free(scene.light);
	free(scene.cam);

	//system("leaks miniRT");
	return(EXIT_SUCCESS);
}
