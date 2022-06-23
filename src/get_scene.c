/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scene.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/23 19:37:26 by bhoitzin      ########   odam.nl         */
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

int	num_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] > 47 && str[i] < 58)
		i++;
	return (i);
}

double	ft_atod(char *str)
{
	int		x;
	int		y;
	double	digit;
	char	**nums;

	nums = ft_split(str, '.');
	x = ft_atoi(nums[0]);
	if (!nums[1])
		y = 0;
	else
		y = ft_atoi(nums[1]);
	digit = y;
	if (nums[1])
		digit /= pow(10, num_strlen(nums[1]));
	if (x < 0)
		digit -= x;
	else
		digit += x;
	if (str[0] == '-')
		digit *= -1;
	free_strstr(nums);
	return (digit);
}

void	count_objects(t_scene *scene, char *str, int fd)
{
	char	**splitted_str;

	while (str)
	{
		splitted_str = ft_split(str, ' ');
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
		free(str);
		free_strstr(splitted_str);
		str = NULL;
		str = get_next_line(fd);
	}
	close(fd);
}

int	set_scene(t_scene *scene, char *name)
{
	int		fd;
	char	*str;
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

void	cb(t_scene *scene, char	**str)
{
	if (strstr_len(str) != 3)
		ft_error(1, "Wrong number of arguments for cb\n");
	scene->cb[ON] = true;
	scene->cb[W] = ft_atoi(str[1]);
	scene->cb[H] = ft_atoi(str[2]);
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
		cb(scene, splitted_str);
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
