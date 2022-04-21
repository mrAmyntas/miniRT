#include "../inc/miniRT.h"

#define WIDTH 1080
#define HEIGHT 720


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
		mlx_set_mouse_pos(data->mlx, WIDTH/2-25, HEIGHT/2-25); //cursor to center with M
}

int32_t	main(int argc, char **argv)
{

	t_data	data;
	t_scene	scene;


	int t = 0;
    int r = 255;
    int g = 0;
    int b = 0;
    int color;
    color = create_trgb(t, r, g , b);
	read_scene(&scene, argv[1]);
    printf("color       :%x  r:%d  g:%d  b:%d  t:%d\n", color, get_r(color), get_g(color), get_b(color), get_t(color));
    data.color = create_trgb(t, r, g , b);
    printf("color       :%x  r:%d  g:%d  b:%d  t:%d\n", data.color, get_r(data.color), get_g(data.color), get_b(data.color), get_t(data.color));


	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.mlx_img = mlx_new_image(data.mlx, 64, 64);
	memset(data.mlx_img->pixels, 255, data.mlx_img->width * data.mlx_img->height * sizeof(int));
	mlx_image_to_window(data.mlx, data.mlx_img, WIDTH/2-25, HEIGHT/2-25);
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