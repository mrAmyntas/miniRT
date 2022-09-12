/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scene_objects.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/09/12 12:59:46 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	read_pl2(t_scene *scene, char **line, int i, char **coords)
{
	scene->pl[i].orth_vec.x = ft_atod(coords[0]);
	scene->pl[i].orth_vec.y = ft_atod(coords[1]);
	scene->pl[i].orth_vec.z = ft_atod(coords[2]);
	if (scene->pl[i].orth_vec.x < -1 || scene->pl[i].orth_vec.x > 1
		|| scene->pl[i].orth_vec.y < -1 || scene->pl[i].orth_vec.y > 1
		|| scene->pl[i].orth_vec.z < -1 || scene->pl[i].orth_vec.z > 1)
		ft_error(1, "One of the vectors for a plane is out of range\n");
	scene->pl[i].orth_vec = normalize_vector(scene->pl[i].orth_vec);
	free_strstr(coords);
	coords = ft_split(line[3], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for a plane\n");
	create_hsl(&scene->pl[i].hsl,
		ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	scene->pl[i].rgb.x = ft_atoi(coords[0]);
	scene->pl[i].rgb.y = ft_atoi(coords[1]);
	scene->pl[i].rgb.z = ft_atoi(coords[2]);
	free_strstr(coords);
}

void	read_pl(t_scene *scene, char **line)
{
	char		**coords;
	static int	i = 0;

	if (strstr_len(line) != 4)
		ft_error(1, "Wrong number of arguments for a plane\n");
	coords = ft_split(line[1], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of coordinates for a plane\n");
	scene->pl[i].coord.x = ft_atod(coords[0]);
	scene->pl[i].coord.y = ft_atod(coords[1]);
	scene->pl[i].coord.z = ft_atod(coords[2]);
	free_strstr(coords);
	coords = ft_split(line[2], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of vectors for a plane\n");
	read_pl2(scene, line, i, coords);
	i++;
}

void	read_sp(t_scene *scene, char **line)
{
	char		**coords;
	static int	i;

	if (strstr_len(line) != 4)
		ft_error(1, "Wrong number of arguments for a sphere\n");
	coords = ft_split(line[1], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of coordinates for a sphere\n");
	scene->sp[i].c.x = ft_atod(coords[0]);
	scene->sp[i].c.y = ft_atod(coords[1]);
	scene->sp[i].c.z = ft_atod(coords[2]);
	free_strstr(coords);
	scene->sp[i].size = ft_atod(line[2]);
	if (scene->sp[i].size <= 0)
		ft_error(1, "illegal size for a sphere\n");
	coords = ft_split(line[3], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of vectors for a sphere\n");
	create_hsl(&scene->sp[i].hsl,
		ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	scene->sp[i].rgb.x = ft_atoi(coords[0]);
	scene->sp[i].rgb.y = ft_atoi(coords[1]);
	scene->sp[i].rgb.z = ft_atoi(coords[2]);
	free_strstr(coords);
	i++;
}

void	read_cy2(t_scene *scene, char **line, int i, char **coords)
{
	scene->cy[i].dir.x = ft_atod(coords[0]);
	scene->cy[i].dir.y = ft_atod(coords[1]);
	scene->cy[i].dir.z = ft_atod(coords[2]);
	if (scene->cy[i].dir.x < 0.000001
		&& scene->cy[i].dir.y < 0.000001 && fabs(scene->cy[i].dir.z) > 0.999999)
		scene->cy[i].dir.y = scene->cy[i].dir.y + 0.00000001;
	if (scene->cy[i].dir.x < -1 || scene->cy[i].dir.x > 1
		|| scene->cy[i].dir.y < -1 || scene->cy[i].dir.y > 1
		|| scene->cy[i].dir.z < -1 || scene->cy[i].dir.z > 1)
		ft_error(1, "One of the vectors for a cylinder is out of range\n");
	scene->cy[i].dir = normalize_vector(scene->cy[i].dir);
	free_strstr(coords);
	scene->cy[i].r = ft_atod(line[3]) / 2;
	scene->cy[i].height = ft_atod(line[4]);
	if (scene->cy[i].r <= 0 || scene->cy[i].height <= 0)
		ft_error(1, "illegal height/radius for a cylinder\n");
	coords = ft_split(line[5], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for a cylinder\n");
	create_hsl(&scene->cy[i].hsl,
		ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	scene->cy[i].rgb.x = ft_atoi(coords[0]);
	scene->cy[i].rgb.y = ft_atoi(coords[1]);
	scene->cy[i].rgb.z = ft_atoi(coords[2]);
	free_strstr(coords);
}

void	read_cy(t_scene *scene, char **line)
{
	char		**coords;
	static int	i = 0;

	scene->cy[i].cap = NOT;
	if (strstr_len(line) != 6)
		ft_error(1, "Wrong number of arguments for a cylinder\n");
	coords = ft_split(line[1], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of coordinates for a cylinder\n");
	scene->cy[i].eye.x = ft_atod(coords[0]);
	scene->cy[i].eye.y = ft_atod(coords[1]);
	scene->cy[i].eye.z = ft_atod(coords[2]);
	free_strstr(coords);
	coords = ft_split(line[2], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of vectors for a cylinder\n");
	read_cy2(scene, line, i, coords);
	set_i_t(&scene->cy[i].eye, &scene->cy[i].i_t);
	set_i_r(&scene->cy[i].dir, &scene->cy[i].i_r);
	i++;
}
