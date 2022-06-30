/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scene.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/30 16:35:42 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"

void	count_objects2(t_scene *scene, char **splitted_str)
{
	if (!strncmp(splitted_str[0], "pl", 3))
		scene->amount[PLANE]++;
	else if (!strncmp(splitted_str[0], "cy", 3))
		scene->amount[CYLINDER]++;
	else if (!strncmp(splitted_str[0], "sp", 3))
		scene->amount[SPHERE]++;
	else if (!strncmp(splitted_str[0], "L", 2))
		scene->amount[LIGHT]++;
	else if (!strncmp(splitted_str[0], "tor", 4))
		scene->amount[TORUS]++;
	else if (!strncmp(splitted_str[0], "di", 3))
		scene->amount[DISC]++;
	else if (!strncmp(splitted_str[0], "A", 2))
		scene->amount[6]++;
	else if (!strncmp(splitted_str[0], "C", 2))
		scene->amount[7]++;
	else if (strncmp(splitted_str[0], "cb", 3)
		&& strncmp(splitted_str[0], "#", 2)
		&& strncmp(splitted_str[0], "\n", 2))
		ft_error(1, "Invalid element(s)\n");
}

void	count_objects(t_scene *scene, char *str, int fd)
{
	char	**splitted_str;

	while (str)
	{
		splitted_str = ft_split(str, ' ');
		free(str);
		count_objects2(scene, splitted_str);
		free_strstr(splitted_str);
		str = NULL;
		str = get_next_line(fd);
	}
	close(fd);
}

int	set_scene(t_scene *scene, char *name)
{
	int		i;

	i = 0;
	scene->cb[ON] = false;
	while (i < 8)
	{
		if (i < 3)
			scene->state[i] = 0;
		scene->amount[i] = 0;
		i++;
	}
	scene->origin.x = 0;
	scene->origin.y = 0;
	scene->origin.z = 0;
	scene->ori_dir.x = 0;
	scene->ori_dir.y = 0;
	scene->ori_dir.z = 1;
	return (open_and_malloc(scene, name));
}

void	find_element(t_scene *scene, char **splitted_str)
{
	if (!strncmp(splitted_str[0], "A", 2))
		read_a(scene, splitted_str);
	else if (!strncmp(splitted_str[0], "C", 2))
		read_c(scene, splitted_str);
	else if (!strncmp(splitted_str[0], "L", 2))
		read_l(scene, splitted_str);
	else if (!strncmp(splitted_str[0], "pl", 3))
		read_pl(scene, splitted_str);
	else if (!strncmp(splitted_str[0], "sp", 3))
		read_sp(scene, splitted_str);
	else if (!strncmp(splitted_str[0], "cy", 3))
		read_cy(scene, splitted_str);
	else if (!strncmp(splitted_str[0], "di", 3))
		read_di(scene, splitted_str);
	else if (!strncmp(splitted_str[0], "tor", 4))
		read_tor(scene, splitted_str);
	else if (!strncmp(splitted_str[0], "cb", 3))
	{
		if (strstr_len(splitted_str) != 3)
			ft_error(1, "Wrong number of arguments for cb\n");
		scene->cb[ON] = true;
		scene->cb[W] = ft_atoi(splitted_str[1]);
		scene->cb[H] = ft_atoi(splitted_str[2]);
	}
}

void	read_scene(t_scene *scene, char *name)
{
	int		fd;
	char	*str;
	char	**splitted_str;

	fd = set_scene(scene, name);
	str = get_next_line(fd);
	while (str)
	{
		splitted_str = ft_split(str, ' ');
		find_element(scene, splitted_str);
		free_strstr(splitted_str);
		free(str);
		str = NULL;
		str = get_next_line(fd);
	}
	free(str);
	str = NULL;
	if (!scene->amount[LIGHT] || !scene->amount[6] || !scene->amount[7])
		ft_error(1, "Element missing\n");
}
