/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/23 18:49:17 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static void	background(t_data *data)
{
	int	i;
	int	j;

	data->mlx_img = mlx_new_image(data->mlx,
			data->width, data->height);
	i = 0;
	while (i < data->width)
	{
		j = 0;
		while (j < data->height)
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
	scene->r.lookatpoint = add_vectors(scene->cam->eye, scene->cam->dir);
	scene->r.viewdir = normalize_vector(
			subtract_vectors(scene->r.lookatpoint, scene->cam->eye));
	scene->r.u = normalize_vector(cross_product(scene->r.viewdir, scene->r.up));
	scene->r.v = normalize_vector(cross_product(scene->r.u, scene->r.viewdir));
	scene->r.viewplanehalfwidth = tan(scene->c_fov * M_PI / 180 / 2);
	scene->r.aspectratio = data->height / data->width;
	scene->r.viewplanehalfheight = scene->r.aspectratio
		* scene->r.viewplanehalfwidth;
	scene->r.tmp = subtract_vectors(scene->r.lookatpoint, multiply_vector(
				scene->r.v, scene->r.viewplanehalfheight));
	scene->r.viewplanebottomleftpoint = subtract_vectors(
			scene->r.tmp, multiply_vector(
				scene->r.u, scene->r.viewplanehalfwidth));
	scene->r.tmp = multiply_vector(
			scene->r.u, (2 * scene->r.viewplanehalfwidth));
	scene->r.x_inc_vector = divide_vec_scalar(scene->r.tmp, data->width);
	scene->r.tmp = multiply_vector(
			scene->r.v, (2 * scene->r.viewplanehalfheight));
	scene->r.y_inc_vector = divide_vec_scalar(scene->r.tmp, data->height);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_scene	scene;

	data.height = 600;
	data.width = 600;
	if (argc != 2)
		ft_error(1, "Invalid amount of arguments\n");
	read_scene(&scene, argv[1]);
	data.mlx = mlx_init(data.width, data.height, "MiniRT", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	set_ray_data(&data, &scene);
	background(&data);
	loop_pixels(&data, &scene);
	mlx_image_to_window(data.mlx, data.mlx_img, 0, 0);
	mlx_loop_hook(data.mlx, &hook, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free(scene.pl);
	free(scene.cy);
	free(scene.sp);
	free(scene.cam);
	return (EXIT_SUCCESS);
}
