#ifndef SCENES_H
# define SCENES_H
# include "vectors.h"
# include <math.h>

typedef struct s_light
{
	double		brightness;
	t_vect3d	ori;
	int			color;
}				t_light;

typedef struct s_cy
{
	t_vect3d	eye;
	t_vect3d	dir;
    double  	diameter;
    double  	height;
    int     	rgb;
	t_vect3d	hsl; // h = x = 0, s = y = 1, l = z = 2
}				t_cy;

typedef struct s_pl
{
	t_vect3d	orth_vec;
	t_vect3d	coord;
    int			rgb;
	t_vect3d	hsl;
}				t_pl;

typedef struct s_sp
{
	t_vect3d	C;
    int     	rgb;
	t_vect3d	coord;
	double		size;
	t_vect3d	hsl;
}				t_sp;

typedef struct 	s_ray {
	t_vect3d	dir;
	t_vect3d	eye;
}				t_ray;

typedef struct s_scene
{
    int     	amount[3];
    int    		state[3];
	double 		a_ratio;
    int    		a_rgb;
	t_vect3d	a_hsl;
    double  	c_fov;
	t_vect3d	current_dir;
	t_ray		*cam;
    t_pl   		*pl;
    t_sp    	*sp;
    t_cy    	*cy;
	t_light		*light;
	t_vect3d	origin;
}				t_scene;

// read objects
void	read_cy(t_scene *scene, char **line);
void	read_sp(t_scene *scene, char **line);
void	read_pl(t_scene *scene, char **line);

// read elements
void	read_a(t_scene *scene, char **line);
void	read_c(t_scene *scene, char **line);
void	read_l(t_scene *scene, char **line);

// Utilities
double	ft_atod(char *str);
void	free_strstr(char **str);
int	    strstr_len(char **str);
void	create_hsl(t_vect3d *hsl, int r, int g, int b);
int	    create_rgb(int r, int g, int b);
void	    ft_error(int num, char *msg);

#endif