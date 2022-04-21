#include "../inc/miniRT.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
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

double  ft_itod(char *str)
{
    int     x;
    int     y;
    double  digit;
    char    **nums;

    nums = ft_split(str, '.');
    x = ft_atoi(nums[0]);
    if (!nums[1])
        y = 0;
    else
        y = ft_atoi(nums[1]);
    digit = y;
    if (nums[1])
        digit /= pow(10, ft_strlen(nums[1]));
    digit += x;
    return (digit);
}

int     read_a(t_scene *scene, char **line)
{
    char    **colours;

    if (scene->state[0])
        return (1);
    scene->state[0] = 1;
    scene->a_ratio = ft_itod(line[1]);
    colours = ft_split(line[2], ',');
    scene->a_rgb = create_rgb(ft_atoi(colours[0]), ft_atoi(colours[1]), ft_atoi(colours[2]));
    free_strstr(colours);
    printf("A: %f %X\n", scene->a_ratio, scene->a_rgb);
    return (0);
}

int     read_c(t_scene *scene, char **line)
{
    char    **coords;

    if (scene->state[1])
        return (1);
    coords = ft_split(line[1], ',');
    scene->c_x[0] = ft_itod(coords[0]);
    scene->c_y[0] = ft_itod(coords[1]);
    scene->c_z[0] = ft_itod(coords[2]);
    free_strstr(coords);
    coords = ft_split(line[2], ',');
    scene->c_x[1] = ft_itod(coords[0]);
    scene->c_y[1] = ft_itod(coords[1]);
    scene->c_z[1] = ft_itod(coords[2]);
    free_strstr(coords);
    scene->c_fov = ft_atoi(line[3]);
    printf("C: %f, %f, %f   %f, %f, %f  %i\n", scene->c_x[0], scene->c_y[0], scene->c_z[0], scene->c_x[1], scene->c_y[1], scene->c_z[1], scene->c_fov);
    return (0);
}

int     read_l(t_scene *scene, char **line)
{
    char    **coords;

    if (scene->state[2])
        return (1);
    coords = ft_split(line[1], ',');
    scene->l_x = ft_itod(coords[0]);
    scene->l_y = ft_itod(coords[1]);
    scene->l_z = ft_itod(coords[2]);
    free_strstr(coords);
    scene->l_bright = ft_itod(line[2]);
    coords = ft_split(line[3], ',');
    scene->l_rgb = create_rgb(ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
    printf("L %f %f %f  %f  %X\n", scene->l_x, scene->l_y, scene->l_z, scene->l_bright, scene->l_rgb);
    return (0);
}

int     read_pl(t_scene *scene, char **line)
{
    printf("...\n");
    return (0);
}

void    read_scene(t_scene *scene, char *name)
{
    char    *str;
    char    **splitted_str;
    int     fd;
    int     ret;

    ret = 0;
    scene->state[0] = 0;
    scene->state[1] = 0;
    scene->state[2] = 0;
    fd = open(name, O_RDONLY);
    str = get_next_line(fd);
    while (str && !ret)
    {
        splitted_str = ft_split(str, ' ');
        if (!strncmp(splitted_str[0], "A", 2))
            ret = read_a(scene, splitted_str);
        else if (!strncmp(splitted_str[0], "C", 2))
            ret = read_c(scene, splitted_str);
        else if (!strncmp(splitted_str[0], "L", 2))
            read_l(scene, splitted_str);
        else if (!strncmp(splitted_str[0], "pl", 3))
            read_pl(scene, splitted_str);
        //else if (!strncmp(splitted_str[0], "sp", 3))
        //    read_sp(scene, splitted_str);
        //else if (!strncmp(splitted_str[0], "cy", 3))
        //    read_cy(scene, splitted_str);
        free_strstr(splitted_str);
        free(str);
        str = NULL;
        str = get_next_line(fd);
    }
    if (ret)
    {
        printf("some kind of error\n");
        exit(ret);
    }
}
