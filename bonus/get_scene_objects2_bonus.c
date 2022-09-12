/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scene_objects2_bonus.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/09/12 13:05:49 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"

void	read_di2(t_scene *scene, char **line, int i, char **coords)
{
	scene->di[i].orth_vec.x = ft_atod(coords[0]);
	scene->di[i].orth_vec.y = ft_atod(coords[1]);
	scene->di[i].orth_vec.z = ft_atod(coords[2]);
	if (scene->di[i].orth_vec.x < -1 || scene->di[i].orth_vec.x > 1
		|| scene->di[i].orth_vec.y < -1 || scene->di[i].orth_vec.y > 1
		|| scene->di[i].orth_vec.z < -1 || scene->di[i].orth_vec.z > 1)
		ft_error(1, "One of the vectors for a disc is out of range\n");
	scene->di[i].orth_vec = normalize_vector(scene->di[i].orth_vec);
	free_strstr(coords);
	scene->di[i].r = ft_atod(line[3]);
	if (scene->di[i].r <= 0 || scene->di[i].r >= 2147483647)
		ft_error(1, "illegal radius for a disc\n");
	coords = ft_split(line[4], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for a disc\n");
	create_hsl(&scene->di[i].hsl,
		ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	create_hsl(&scene->di[i].lsh, 255 - ft_atoi(coords[0]),
		255 - ft_atoi(coords[1]), 255 - ft_atoi(coords[2]));
	scene->di[i].rgb.x = ft_atoi(coords[0]);
	scene->di[i].rgb.y = ft_atoi(coords[1]);
	scene->di[i].rgb.z = ft_atoi(coords[2]);
	free_strstr(coords);
}

void	read_di(t_scene *scene, char **line)
{
	char		**coords;
	static int	i = 0;

	if (strstr_len(line) != 5)
		ft_error(1, "Wrong number of arguments for a disc\n");
	coords = ft_split(line[1], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of coordinates for a disc\n");
	scene->di[i].coord.x = ft_atod(coords[0]);
	scene->di[i].coord.y = ft_atod(coords[1]);
	scene->di[i].coord.z = ft_atod(coords[2]);
	free_strstr(coords);
	coords = ft_split(line[2], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of vectors for a disc\n");
	read_di2(scene, line, i, coords);
	scene->di[i].checker = 0;
	i++;
}

void	read_tor3(t_scene *scene, char **line, int i, char **coords)
{
		scene->tor[i].dir = normalize_vector(scene->tor[i].dir);
	free_strstr(coords);
	scene->tor[i].r_cir = ft_atod(line[3]);
	scene->tor[i].r_tube = ft_atod(line[4]);
	if (scene->tor[i].r_cir <= 0 || scene->tor[i].r_tube <= 0
		|| scene->tor[i].r_cir >= INT_MAX || scene->tor[i].r_tube >= INT_MAX)
		ft_error(1, "illegal radius for a torus\n");
	if (scene->tor[i].r_cir < scene->tor[i].r_tube)
		ft_error(1, "Radius of circle has to be bigger then radius of tube\n");
	coords = ft_split(line[5], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for a torus\n");
	create_hsl(&scene->tor[i].hsl,
		ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	create_hsl(&scene->tor[i].lsh, 255 - ft_atoi(coords[0]),
		255 - ft_atoi(coords[1]), 255 - ft_atoi(coords[2]));
	scene->tor[i].rgb.x = ft_atoi(coords[0]);
	scene->tor[i].rgb.y = ft_atoi(coords[1]);
	scene->tor[i].rgb.z = ft_atoi(coords[2]);
	free_strstr(coords);
}

void	read_tor2(t_scene *scene, char **line, int i, char **coords)
{
	scene->tor[i].dir.x = ft_atod(coords[0]);
	scene->tor[i].dir.y = ft_atod(coords[1]);
	scene->tor[i].dir.z = ft_atod(coords[2]);
	if (fabs(scene->tor[i].dir.x) < 0.00001 && fabs(scene->tor[i].dir.y)
		< 0.00001 && fabs(scene->tor[i].dir.z) > 0.999999)
		scene->tor[i].dir.x = scene->tor[i].dir.x + 0.000001;
	if (fabs(scene->tor[i].dir.x) < 0.00001 && fabs(scene->tor[i].dir.z)
		< 0.00001 && fabs(scene->tor[i].dir.y) > 0.999999)
		scene->tor[i].dir.x = scene->tor[i].dir.x + 0.000001;
	if (fabs(scene->tor[i].dir.y) < 0.00001 && fabs(scene->tor[i].dir.z)
		< 0.00001 && fabs(scene->tor[i].dir.x) > 0.999999)
		scene->tor[i].dir.x = scene->tor[i].dir.y + 0.000001;
	if (scene->tor[i].dir.x < -1 || scene->tor[i].dir.x > 1
		|| scene->tor[i].dir.y < -1 || scene->tor[i].dir.y > 1
		|| scene->tor[i].dir.z < -1 || scene->tor[i].dir.z > 1)
		ft_error(1, "One of the vectors for a torus is out of range\n");
	read_tor3(scene, line, i, coords);
}

void	read_tor(t_scene *scene, char **line)
{
	char		**coords;
	static int	i = 0;

	if (strstr_len(line) != 6)
		ft_error(1, "Wrong number of arguments for a torus\n");
	coords = ft_split(line[1], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of coordinates for a torus\n");
	scene->tor[i].coord.x = ft_atod(coords[0]);
	scene->tor[i].coord.y = ft_atod(coords[1]);
	scene->tor[i].coord.z = ft_atod(coords[2]);
	free_strstr(coords);
	coords = ft_split(line[2], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of vectors for a torus\n");
	read_tor2(scene, line, i, coords);
	set_i_t(&scene->tor[i].coord, &scene->tor[i].i_t);
	set_i_r(&scene->tor[i].dir, &scene->tor[i].i_r);
	set_r_tor(scene, i);
	scene->tor[i].checker = 0;
	i++;
}
