#include "../inc/miniRT.h"
#include "../inc/scenes.h"

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
	create_hsl(&scene->pl[i].hsl, ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	scene->pl[i].rgb = create_rgb(ft_atoi(coords[0]),
			ft_atoi(coords[1]), ft_atoi(coords[2]), ft_strjoin("plane ", ft_itoa(i)));
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
	scene->sp[i].C.x = ft_atod(coords[0]);
	scene->sp[i].C.y = ft_atod(coords[1]);
	scene->sp[i].C.z = ft_atod(coords[2]);
	free_strstr(coords);
	scene->sp[i].size = ft_atod(line[2]);
	coords = ft_split(line[3], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of vectors for a sphere\n");
	create_hsl(&scene->sp[i].hsl, ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	create_hsl(&scene->sp[i].lsh, 255 - ft_atoi(coords[0]), 255 - ft_atoi(coords[1]), 255 - ft_atoi(coords[2]));
	//printf("%i %i, %i %i %i\n", hsl_to_rgb(scene->sp[i].hsl), hsl_to_rgb(scene->sp[i].lsh), 255 - ft_atoi(coords[0]), 255 - ft_atoi(coords[1]), 255 - ft_atoi(coords[2]));
	// printf("%i %i %i\n", 255 - ft_atoi(coords[0]), 255 - ft_atoi(coords[1]), 255 - ft_atoi(coords[2]));
	scene->sp[i].rgb = create_rgb(ft_atoi(coords[0]),
			ft_atoi(coords[1]), ft_atoi(coords[2]), ft_strjoin("sphere ", ft_itoa(i)));
	i++;
}

void	read_cy2(t_scene *scene, char **line, int i, char **coords)
{
	scene->cy[i].dir.x = ft_atod(coords[0]);
	scene->cy[i].dir.y = ft_atod(coords[1]);
	scene->cy[i].dir.z = ft_atod(coords[2]);
	if (scene->cy[i].dir.x < 0.000001 && scene->cy[i].dir.y < 0.000001 && fabs(scene->cy[i].dir.z) > 0.999999)
		scene->cy[i].dir.y = scene->cy[i].dir.y + 0.00000001;
	if (scene->cy[i].dir.x < -1 || scene->cy[i].dir.x > 1
		|| scene->cy[i].dir.y < -1 || scene->cy[i].dir.y > 1
		|| scene->cy[i].dir.z < -1 || scene->cy[i].dir.z > 1)
		ft_error(1, "One of the vectors for a cylinder is out of range\n");
	scene->cy[i].dir = normalize_vector(scene->cy[i].dir);
	free_strstr(coords);
	scene->cy[i].r = ft_atod(line[3]) / 2;
	scene->cy[i].height = ft_atod(line[4]);
	coords = ft_split(line[5], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for a cylinder\n");
	create_hsl(&scene->cy[i].hsl, ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	scene->cy[i].rgb = create_rgb(ft_atoi(coords[0]),
			ft_atoi(coords[1]), ft_atoi(coords[2]), ft_strjoin("cylinder ", ft_itoa(i)));
	set_i_t(scene, i);
	set_i_r(scene, i);
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
	i++;
}

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
	coords = ft_split(line[4], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for a disc\n");
	create_hsl(&scene->di[i].hsl, ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	scene->di[i].rgb = create_rgb(ft_atoi(coords[0]),
			ft_atoi(coords[1]), ft_atoi(coords[2]), ft_strjoin("disc ", ft_itoa(i)));
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
	i++;
}

void	read_tor2(t_scene *scene, char **line, int i, char **coords)
{
	scene->tor[i].dir.x = ft_atod(coords[0]);
	scene->tor[i].dir.y = ft_atod(coords[1]);
	scene->tor[i].dir.z = ft_atod(coords[2]);
	if (scene->tor[i].dir.x < 0.000001 && scene->tor[i].dir.y < 0.000001 && fabs(scene->tor[i].dir.z) > 0.999999)
		scene->tor[i].dir.y = scene->tor[i].dir.y + 0.00000001;
	if (scene->tor[i].dir.x < -1 || scene->tor[i].dir.x > 1
		|| scene->tor[i].dir.y < -1 || scene->tor[i].dir.y > 1
		|| scene->tor[i].dir.z < -1 || scene->tor[i].dir.z > 1)
		ft_error(1, "One of the vectors for a torus is out of range\n");
	scene->tor[i].dir = normalize_vector(scene->tor[i].dir);
	free_strstr(coords);
	scene->tor[i].R_cir = ft_atod(line[3]);
	scene->tor[i].r_tube = ft_atod(line[4]);
	coords = ft_split(line[5], ',');
	if (strstr_len(coords) != 3)
		ft_error(1, "Wrong number of colours for a torus\n");
	create_hsl(&scene->tor[i].hsl, ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2]));
	scene->tor[i].rgb = create_rgb(ft_atoi(coords[0]),
			ft_atoi(coords[1]), ft_atoi(coords[2]), ft_strjoin("torus ", ft_itoa(i)));
	free_strstr(coords);
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
	set_i_t_tor(scene, i);
	set_i_r_tor(scene, i);
	i++;
}