#include "../inc/miniRT.h"

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

int     read_a(t_scene *scene, char **line)
{
    int colour;

    if (scene->state[0])
        return (1);
    scene->state[0] = 1;
    colour = create_trgb(24, ft_atoi(line[2]), ft_atoi(line[3]), ft_atoi(line[4]));
    printf("%i\n", colour);
    return (0);
}

void    read_scene(t_scene *scene, char *name)
{
    char    *str;
    char    **splitted_str;
    int     fd;

    scene->state[0] = 0;
    scene->state[1] = 0;
    scene->state[2] = 0;
    fd = open(ft_strjoin("../scenes/", name), O_RDONLY);
    str = get_next_line(fd);
    while (str)
    {
        splitted_str = ft_split(str, ' ');
        if (!strncmp(splitted_str[0], "A", 2))
            read_a(scene, splitted_str);
        //else if (!strncmp(splitted_str[0], "C", 2))
        //    read_c(scene, splitted_str);
        //else if (!strncmp(splitted_str[0], "L", 2))
        //    read_l(scene, splitted_str);
        //else if (!strncmp(splitted_str[0], "pl", 3))
        //    read_pl(scene, splitted_str);
        //else if (!strncmp(splitted_str[0], "sp", 3))
        //    read_sp(scene, splitted_str);
        //else if (!strncmp(splitted_str[0], "cy", 3))
        //    read_cy(scene, splitted_str);
        free_strstr(splitted_str);
        free(str);
        str = NULL;
        str = get_next_line(fd);
    }
}
