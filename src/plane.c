#include "../inc/miniRT.h"

int	plane(t_data *data)
{
	data->mlx = mlx_init(data->width, data->height, "MLX42", true);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->mlx_img = mlx_new_image(data->mlx, 64, 64);
	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->mlx_img, data->width/2-25, data->height/2-25);
	mlx_loop_hook(data->mlx, &hook, &data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return 0;
}