#include "../inc/miniRT.h"

static void	background(t_data *data, t_scene *scene)
{
	int			i;
	int			j;

	data->mlx_img = mlx_new_image(data->mlx,
			data->width + 10, data->height + 10);
	i = 0;
	while (i < data->width + 1)
	{
		j = 0;
		while (j < data->height + 1)
		{
			mlx_put_pixel(data->mlx_img, i, j, 0x000000FF);
			j++;
		}
		i++;
	}
}

void	hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

void	set_ray_data(t_data *data, t_scene *scene)
{
	scene->r.up.x = 0;
	scene->r.up.y = 1;
	scene->r.up.z = 0;
	scene->r.LookAtPoint = add_vectors(scene->cam->eye, scene->cam->dir);
	scene->r.viewDir = normalize_vector(
			subtract_vectors(scene->r.LookAtPoint, scene->cam->eye));
	scene->r.U = normalize_vector(cross_product(scene->r.viewDir, scene->r.up));
	scene->r.V = normalize_vector(cross_product(scene->r.U, scene->r.viewDir));
	scene->r.viewPlaneHalfWidth = tan(scene->c_fov * M_PI / 180 / 2);
	scene->r.aspectRatio = data->height / data->width;
	scene->r.viewPlaneHalfHeight = scene->r.aspectRatio
		* scene->r.viewPlaneHalfWidth;
	scene->r.tmp = subtract_vectors(scene->r.LookAtPoint, multiply_vector(
				scene->r.V, scene->r.viewPlaneHalfHeight));
	scene->r.viewPlaneBottomLeftPoint = subtract_vectors(
			scene->r.tmp, multiply_vector(
				scene->r.U, scene->r.viewPlaneHalfWidth));
	scene->r.tmp = multiply_vector(
			scene->r.U, (2 * scene->r.viewPlaneHalfWidth));
	scene->r.xIncVector = divide_vec_scalar(scene->r.tmp, data->width);
	scene->r.tmp = multiply_vector(
			scene->r.V, (2 * scene->r.viewPlaneHalfHeight));
	scene->r.yIncVector = divide_vec_scalar(scene->r.tmp, data->height);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_scene	scene;

	data.height = 1080;
	data.width = 1900;
	if (argc != 2)
		ft_error(1, "Invalid amount of arguments\n");
	read_scene(&scene, argv[1]);
	data.mlx = mlx_init(data.width, data.height, "MiniRT", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	set_ray_data(&data, &scene);
	background(&data, &scene);
	loop_pixels(&data, &scene);
	mlx_image_to_window(data.mlx, data.mlx_img, -1, -1);
	mlx_loop_hook(data.mlx, &hook, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free(scene.pl);
	free(scene.cy);
	free(scene.sp);
	free(scene.light);
	free(scene.cam);
	//system("leaks miniRT");
	return (EXIT_SUCCESS);
}
