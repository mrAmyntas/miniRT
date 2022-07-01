/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scene_elements_bonus.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/07/01 17:21:48 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inc/scenes.h"

void	read_a(t_scene *scene, char **line)
{
	char	**colours;

	if (scene->state[0])
		ft_error(1, "Ambient lighting can only be declared once\n");
	if (strstr_len(line) != 3)
		ft_error(1, "Wrong number of arguments for ambient lighting\n");
	scene->state[0] = 1;
	scene->a_ratio = ft_atod(line[1]);
	if (scene->a_ratio < 0 || scene->a_ratio > 1)
		ft_error(1, "Ambient lighting ratio is out of range\n");
	colours = ft_split(line[2], ',');
	if (strstr_len(colours) != 3)
		ft_error(1, "Wrong number of colours for ambient lighting\n");
	create_hsl(&scene->a_hsl,
		ft_atoi(colours[0]), ft_atoi(colours[1]), ft_atoi(colours[2]));
	scene->a_rgb.x = ft_atoi(colours[0]);
	scene->a_rgb.y = ft_atoi(colours[1]);
	scene->a_rgb.z = ft_atoi(colours[2]);
	free_strstr(colours);
}

void	read_c2(t_scene *scene, char **line, char **coords)
{
	scene->cam->dir.x = ft_atod(coords[0]);
	scene->cam->dir.y = ft_atod(coords[1]);
	scene->cam->dir.z = ft_atod(coords[2]);
	if (scene->cam->dir.x < -1 || scene->cam->dir.x > 1
		|| scene->cam->dir.y < -1 || scene->cam->dir.y > 1
		|| scene->cam->dir.z < -1 || scene->cam->dir.z > 1)
		ft_error(1, "One of the vectors for camera is out of range\n");
	scene->cam->dir = normalize_vector(scene->cam->dir);
	if (scene->cam->dir.x < 0.00001
		&& fabs(scene->cam->dir.y) > 0.9999 && scene->cam->dir.z < 0.00001)
			scene->cam->dir.z = 0.0001;
	free_strstr(coords);
	scene->c_fov = ft_atoi(line[3]);
}

void	read_c(t_scene *scene, char **line)
{
	char	**coords;

	if (scene->state[1])
		ft_error(1, "Camera can only be declared once\n");
	if (strstr_len(line) != 4)
		ft_error(1, "Wrong number of arguments for camera\n");
	coords = ft_split(line[1], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of coordinates for camera\n");
	scene->cam->eye.x = ft_atod(coords[0]);
	scene->cam->eye.y = ft_atod(coords[1]);
	scene->cam->eye.z = ft_atod(coords[2]);
	free_strstr(coords);
	coords = ft_split(line[2], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of vectors for camera\n");
	read_c2(scene, line, coords);
}

void	read_l(t_scene *scene, char **line)
{
	char		**coords;
	static int	i = 0;

	if (scene->state[2])
		ft_error(1, "Light can only be declared once\n");
	if (strstr_len(line) != 4)
		ft_error(1, "Wrong number of arguments for light\n");
	coords = ft_split(line[1], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of coordinates for light\n");
	scene->light[i].ori.x = ft_atod(coords[0]);
	scene->light[i].ori.y = ft_atod(coords[1]);
	scene->light[i].ori.z = ft_atod(coords[2]);
	free_strstr(coords);
	scene->light[i].kd = 1 * ft_atod(line[2]);
	scene->light[i].ks = 0.4 * ft_atod(line[2]);
	coords = ft_split(line[3], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for light\n");
	scene->light[i].color.x = ft_atoi(coords[0]);
	scene->light[i].color.y = ft_atoi(coords[1]);
	scene->light[i].color.z = ft_atoi(coords[2]);
	free_strstr(coords);
	i++;
}

//some edge-cases happen with light and camera
//at the exact same position, math-stuff
//so offset a tiny bit
void	offset_light_from_cam(t_scene *scene)
{
	int	i;

	i = 0;
	if (compare_vectors(scene->light[i].ori, scene->cam->eye))
			scene->light[i].ori.x = scene->light[i].ori.x + 0.0001;
	while (i < scene->amount[5])
	{
		if (compare_vectors(scene->light[i].ori, scene->cam->eye))
			scene->light[i].ori.x = scene->light[i].ori.x + 0.0001;
		i++;
	}
}
