#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include <memory.h>
# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct	s_vector {
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct 	s_ray {
	t_vector	dir;
	t_vector	eye;
}				t_ray;

typedef struct s_data {
	mlx_image_t	*mlx_img;
	mlx_image_t	*mlx_img2;
	mlx_t		*mlx;
	int			color;
	int			width;
	int			height;
}	t_data;

typedef struct s_pl
{
	t_vector	orth_vec;
	t_vector	coord;
    int			rgb;
}				t_pl;

typedef struct s_sp
{
	double  	x;
    double 		y;
    double  	z;
    int     	rgb;
	//VECTOR iPV 3 DOUBLES! :))))
	t_vector	coord;
	double		radius;

}				t_sp;

typedef struct s_cy
{
	double  x[2];
    double  y[2];
    double  z[2];
    double  diameter;
    double  height;
    int     rgb;
}				t_cy;

typedef struct s_light
{
	double		brightness;
	t_vector	ori;
	int			color;
}				t_light;


typedef struct s_scene
{
    int     amount[3];
    int     state[3];
	double  a_ratio;
    int     a_rgb;
    double  c_fov;
	t_ray	*cam;
    t_pl    *pl;
    t_sp    *sp;
    t_cy    *cy;
	t_light	*light;
}				t_scene;

char		*get_next_line(int fd);
void		hook(void *param);
void		read_scene(t_scene *scene, char *name);
void		ft_error(int num, char *msg);

// *** GLOBE STUFF

void		globe(t_data *data, t_scene *scene);


// *** PLANE STUFF ***

void		draw_plane(t_data *data, t_scene *scene, int num);
int			plane(t_data *data, t_scene *scene, int num);
bool		intersect_eye_plane(t_scene *scene, t_vector *vec1, int num);
bool		is_P_on_plane(t_scene *scene, t_vector P, int num);

// *** VECTOR STUFF ***

t_vector	add_vectors(t_vector vec1, t_vector vec2);
t_vector 	subtract_vectors(t_vector vec1, t_vector vec2);
t_vector 	multiply_vector(t_vector vec1, double factor);
double		dot_product(t_vector vec1, t_vector vec2);

// *** COLOUR STUFF ***
int			create_rgbt(int r, int g, int b, int t);
int			get_t(int rgbt);
int			get_r(int rgbt);
int			get_g(int rgbt);
int			get_b(int rgbt);
int 		add_shade(double distance, int color);
int 		get_opposite(int color);

#endif
