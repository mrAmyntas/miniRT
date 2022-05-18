#include "../inc/miniRT.h"

void	    ft_error(int num, char *msg)
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

int	create_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255)
		ft_error(1, "R colour out of range\n");
	if (g < 0 || r > 255)
		ft_error(1, "G colour out of range\n");
	if (b < 0 || r > 255)
		ft_error(1, "B colour out of range\n");
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
			scene->amount[0]++;
		else if (!strncmp(splitted_str[0], "sp", 3))
			scene->amount[1]++;
		else if (!strncmp(splitted_str[0], "cy", 3))
			scene->amount[2]++;
		else if (strncmp(splitted_str[0], "A", 2)
			&& strncmp(splitted_str[0], "C", 2)
			&& strncmp(splitted_str[0], "L", 2)
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

	scene->state[0] = 0;
	scene->state[1] = 0;
	scene->state[2] = 0;
	scene->amount[0] = 0;
	scene->amount[1] = 0;
	scene->amount[2] = 0;
	scene->origin.x = 0;
	scene->origin.y = 0;
	scene->origin.z = 0;
	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_error(-1, "Open failed");
	str = get_next_line(fd);
	count_objects(scene, str, fd);
	fd = open(name, O_RDONLY);
	scene->pl = malloc(sizeof(t_pl) * (scene->amount[0] + 2));
	scene->sp = malloc(sizeof(t_sp) * (scene->amount[1] + 3));
	scene->cy = malloc(sizeof(t_cy) * (scene->amount[2] + 2));
	scene->cam = malloc(sizeof(t_ray));
	scene->light = malloc(sizeof(t_light));
	if (!scene->pl || !scene->sp || !scene->cy)
		ft_error(1, "Malloc error\n");
	return (fd);
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
}
