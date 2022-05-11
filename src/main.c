#include "../inc/miniRT.h"

double	smallest(double t[3])
{
	if ((t[0] < t[1] || t[1] < 0) && (t[0] < t[2] || t[2] < 0) && t[0] > 0)
		return (t[0]);
	else if ((t[1] < t[2] || t[2] < 0) && t[1] > 0)
		return (t[1]);
	else if (t[2] > 0)
		return (t[2]);
	return (-1);
}

double	find_closest_object(t_scene *scene, t_ray *ray, int *num)
{
	double	t[4];
	int		i;
	int		numb[3];

	t[0] = cast_ray_to_space_check_if_hit_pl(scene, ray, &numb[0]);
	t[1] = cast_ray_to_space_check_if_hit_cy(scene, ray, &numb[1]);
	numb[2] = find_hit_sphere(scene, *ray, scene->amount[1], &t[2]);
	t[3] = smallest(t);
//	printf("t0:%f         t1:%f         t2:%f          t3:%f\n", t[0], t[1], t[2], t[3]);
	if (comp_d(t[0], t[3]))
		*num = 0;
	else if (comp_d(t[1], t[3]))
		*num = 1;
	else if (comp_d(t[2], t[3]))
		*num = 2;
	else
		*num = -1;
	return (t[0]);
}

void	charge_my_lasers(t_data *data, t_scene *scene, int x, int y)
{
	t_ray	ray;
	double	t;
	int		num;

	ray = get_ray(scene, data, x, y);
	t = find_closest_object(scene, &ray, &num);
	if (t != -1)
		mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), scene->pl[0].rgb);
//	if (num != 0 && num != -1)
//		printf("num:%d\n", num);
}

void	positions_my_lasers(t_data *data, t_scene *scene)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width + 1)
	{
		y = 0;
		while (y < data->height + 1)
		{
			charge_my_lasers(data, scene, x, y);
			y++;
		}
		x++;
	}
}

static void	background(t_data *data, t_scene *scene)
{
	int			i;
	int			j;

	data->mlx_img = mlx_new_image(data->mlx, data->width + 10, data->height + 10);
	i = 0;
	//scene->a_hsl.z = scene->a_ratio;
	//scene->a_rgb = hsl_to_rgb(scene->a_hsl);
	scene->a_rgb = 0x000000FF;
	while (i < data->width + 1)
	{
		j = 0;
		while (j < data->height + 1)
		{
			mlx_put_pixel(data->mlx_img, i, j, scene->a_rgb);
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
	data.mlx = mlx_init(data.width, data.height, "MiniRT", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	background(&data, &scene);
	//positions_my_lasers(&data, &scene);
	//plane(&data, &scene);
	sphere(&data, &scene);
	//cylinder(&data, &scene);
	//mlx_image_to_window(data.mlx, data.mlx_img, -1, -1);
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
