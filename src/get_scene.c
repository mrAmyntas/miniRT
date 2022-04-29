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
	scene->a_rgb = create_rgb(ft_atoi(colours[0]),
			ft_atoi(colours[1]), ft_atoi(colours[2]));
	free_strstr(colours);
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
	scene->cam->dir.x = ft_atod(coords[0]);
	scene->cam->dir.y = ft_atod(coords[1]);
	scene->cam->dir.z = ft_atod(coords[2]);
	if (scene->cam->dir.x < -1 || scene->cam->dir.x > 1 || scene->cam->dir.y < -1
		|| scene->cam->dir.y > 1 || scene->cam->dir.z < -1 || scene->cam->dir.z > 1)
		ft_error(1, "One of the vectors for camera is out of range\n");
	free_strstr(coords);
	scene->c_fov = ft_atoi(line[3]);
}

void	read_l(t_scene *scene, char **line)
{
	char	**coords;

	if (scene->state[2])
		ft_error(1, "Light can only be declared once\n");
	if (strstr_len(line) != 4)
		ft_error(1, "Wrong number of arguments for light\n");
	coords = ft_split(line[1], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of coordinates for light\n");
	scene->light->ori.x = ft_atod(coords[0]);
	scene->light->ori.y = ft_atod(coords[1]);
	scene->light->ori.z = ft_atod(coords[2]);
	free_strstr(coords);
	scene->light->brightness = ft_atod(line[2]);
	coords = ft_split(line[3], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for light\n");
	scene->light->color = create_rgb(ft_atoi(coords[0]),
			ft_atoi(coords[1]), ft_atoi(coords[2]));
	free_strstr(coords);
}

void	read_pl2(t_scene *scene, char **line, int i, char **coords)
{
	scene->pl[i].orth_vec.x = ft_atod(coords[0]);
	scene->pl[i].orth_vec.y = ft_atod(coords[1]);
	scene->pl[i].orth_vec.z = ft_atod(coords[2]);
	if (scene->pl[i].orth_vec.x < -1 || scene->pl[i].orth_vec.x > 1
		|| scene->pl[i].orth_vec.y < -1 || scene->pl[i].orth_vec.y > 1
		|| scene->pl[i].orth_vec.z < -1 || scene->pl[i].orth_vec.z > 1)
		ft_error(1, "One of the vectors for a plane is out of range\n");
	free_strstr(coords);
	coords = ft_split(line[3], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for a plane\n");
	scene->pl[i].rgb = create_rgb(ft_atoi(coords[0]),
			ft_atoi(coords[1]), ft_atoi(coords[2]));
	free_strstr(coords);
}

void	read_pl(t_scene *scene, char **line)
{
	char		**coords;
	static int	i;

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
	scene->sp[i].x = ft_atod(coords[0]);
	scene->sp[i].y = ft_atod(coords[1]);
	scene->sp[i].z = ft_atod(coords[2]);
	free_strstr(coords);
	scene->sp[i].size = ft_atod(line[2]);
	coords = ft_split(line[3], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of vectors for a sphere\n");
	scene->sp[i].rgb = create_rgb(ft_atoi(coords[0]),
			ft_atoi(coords[1]), ft_atoi(coords[2]));
	i++;
}

void	read_cy2(t_scene *scene, char **line, int i, char **coords)
{
	scene->cy[i].x[1] = ft_atod(coords[0]);
	scene->cy[i].y[1] = ft_atod(coords[1]);
	scene->cy[i].z[1] = ft_atod(coords[2]);
	if (scene->cy[i].x[1] < -1 || scene->cy[i].x[1] > 1
		|| scene->cy[i].y[1] < -1 || scene->cy[i].y[1] > 1
		|| scene->cy[i].z[1] < -1 || scene->cy[i].z[1] > 1)
		ft_error(1, "One of the vectors for a cylinder is out of range\n");
	free_strstr(coords);
	scene->cy[i].diameter = ft_atod(line[3]);
	scene->cy[i].height = ft_atod(line[4]);
	coords = ft_split(line[5], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for a cylinder\n");
	scene->cy[i].rgb = create_rgb(ft_atoi(coords[0]),
			ft_atoi(coords[1]), ft_atoi(coords[2]));
}

void	read_cy(t_scene *scene, char **line)
{
	char		**coords;
	static int	i;

	if (strstr_len(line) != 6)
		ft_error(1, "Wrong number of arguments for a cylinder\n");
	coords = ft_split(line[1], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of coordinates for a cylinder\n");
	scene->cy[i].x[0] = ft_atod(coords[0]);
	scene->cy[i].y[0] = ft_atod(coords[1]);
	scene->cy[i].z[0] = ft_atod(coords[2]);
	free_strstr(coords);
	coords = ft_split(line[2], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of vectors for a cylinder\n");
	read_cy2(scene, line, i, coords);
	i++;
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
	scene->pl = malloc(sizeof(t_pl) * (scene->state[0] + 2));
	scene->sp = malloc(sizeof(t_sp) * (scene->state[1] + 2));
	scene->cy = malloc(sizeof(t_cy) * (scene->state[2] + 2));
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
