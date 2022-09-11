/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/09/11 14:40:52 by bhoitzin      ########   odam.nl         */
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
		write(2, msg, (size_t)ft_strlen(msg));
	exit(num);
}

uint32_t	create_rgb(double r, double g, double b, char *object)
{
	if ((uint32_t)r < 0 || (uint32_t)r > 255)
		ft_error(1, ft_strjoin("R colour out of range for: ", object));
	if ((uint32_t)g < 0 || (uint32_t)r > 255)
		ft_error(1, ft_strjoin("R colour out of range for: ", object));
	if ((uint32_t)b < 0 || (uint32_t)r > 255)
		ft_error(1, ft_strjoin("R colour out of range for: ", object));
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | 255);
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
	scene->pl = (t_pl *)malloc(sizeof(t_pl)
			* (unsigned long)(scene->amount[PLANE] + 2));
	scene->sp = (t_sp *)malloc(sizeof(t_sp)
			* (unsigned long)(scene->amount[SPHERE] + 3));
	scene->cy = (t_cy *)malloc(sizeof(t_cy)
			* (unsigned long)(scene->amount[CYLINDER] + 3));
	scene->cam = (t_ray *)malloc(sizeof(t_ray));
	scene->light = (t_light *)malloc(sizeof(t_light)
			* (unsigned long)(scene->amount[LIGHT] + 2));
	if (!scene->pl || !scene->sp || !scene->cy || !scene->cam || !scene->light)
		ft_error(1, "Malloc error in open_and_malloc\n");
	return (fd);
}
