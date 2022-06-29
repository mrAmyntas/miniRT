/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/29 18:02:22 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	ft_error(int num, char *msg)
{
	write(2, "Error\n", 6);
	if (num == -1)
	{
		perror(msg);
		exit(1);
	}
	else
		write(2, msg, ft_strlen(msg));
	exit(num);
}

int	create_rgb(int r, int g, int b, char *object)
{
	if (r < 0 || r > 255)
		ft_error(1, ft_strjoin("R colour out of range for: ", object));
	if (g < 0 || r > 255)
		ft_error(1, ft_strjoin("R colour out of range for: ", object));
	if (b < 0 || r > 255)
		ft_error(1, ft_strjoin("R colour out of range for: ", object));
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	strstr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_strstr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

int	open_and_malloc(t_scene *scene, char *name)
{
	int		fd;
	char	*str;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_error(-1, "Open failed");
	str = get_next_line(fd);
	count_objects(scene, str, fd);
	fd = open(name, O_RDONLY);
	scene->pl = (t_pl *)malloc(sizeof(t_pl) * (scene->amount[PLANE] + 2));
	scene->sp = (t_sp *)malloc(sizeof(t_sp) * (scene->amount[SPHERE] + 3));
	scene->cy = (t_cy *)malloc(sizeof(t_cy) * (scene->amount[CYLINDER] + 3));
	scene->di = (t_di *)malloc(sizeof(t_di) * (scene->amount[DISC] + 2));
	scene->tor = (t_tor *)malloc(sizeof(t_tor) * (scene->amount[TORUS] + 2));
	scene->cam = (t_ray *)malloc(sizeof(t_ray));
	scene->light = (t_light *)malloc(sizeof(t_light)
			* (scene->amount[LIGHT] + 2));
	if (!scene->pl || !scene->sp || !scene->cy)
		ft_error(1, "Malloc error\n");
	return (fd);
}
