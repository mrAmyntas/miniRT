#include "../inc/miniRT.h"

#define WIDTH 1080
#define HEIGHT 720


typedef struct 	s_data {

	mlx_image_t	*mlx_img;
	mlx_t		*mlx;
}				t_data;

void	hook(void *param)
{
	t_data *data = param;
	
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
}

int32_t	main(void)
{

	t_data data;

	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.mlx_img = mlx_new_image(data.mlx, 64, 64);
	memset(data.mlx_img->pixels, 255, data.mlx_img->width * data.mlx_img->height * sizeof(int));
	mlx_image_to_window(data.mlx, data.mlx_img, 0, 0);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}

//Plane:
//pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
//identifier: pl
//x,y,z coordinates: 0.0,0.0,-10.0
//3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
//R,G,B colors in range [0-255]: 0, 0, 255