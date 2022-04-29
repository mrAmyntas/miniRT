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

typedef struct	s_vect3d {
	double		x;
	double		y;
	double		z;
}				t_vect3d;

typedef struct 	s_matrix3x3 {
	t_vect3d	col1;
	t_vect3d	col2;
	t_vect3d	col3;
}				t_matrix3x3;

typedef struct 	s_ray {
	t_vect3d	dir;
	t_vect3d	eye;
}				t_ray;

typedef struct 	s_data {
	mlx_image_t	*mlx_img;
	mlx_image_t	*mlx_img2;
	mlx_t		*mlx;
	int			color;
	double		width;
	double		height;
}				t_data;

typedef struct 	s_matrix {
	t_vect3d	col;
	t_vect3d	row;
}				t_matrix;

typedef struct s_pl
{
	t_vect3d	orth_vec;
	t_vect3d	coord;
    int			rgb;
}				t_pl;

typedef struct s_sp
{
	double  	x;
    double 		y;
    double  	z;
    int     	rgb;
	//VECTOR iPV 3 DOUBLES! :))))
	t_vect3d	coord;
	double		size;

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
	t_vect3d	ori;
	int			color;
}				t_light;


typedef struct s_scene
{
    int     	amount[3];
    int    		state[3];
	double 		a_ratio;
    int    		a_rgb;
    double  	c_fov;
	t_vect3d	current_dir;
	t_ray		*cam;
    t_pl   		*pl;
    t_sp    	*sp;
    t_cy    	*cy;
	t_light		*light;
	t_vect3d	origin;
}				t_scene;

char		*get_next_line(int fd);
void		hook(void *param);
void		read_scene(t_scene *scene, char *name);
void		ft_error(int num, char *msg);

// *** GLOBE STUFF \\

void		sphere(t_data *data, t_scene *scene);


// *** PLANE STUFF *** \\

void		draw_plane(t_data *data, t_scene *scene, int num);
int			plane(t_data *data, t_scene *scene);
bool		intersect_eye_plane(t_scene *scene, t_vect3d *vec1, int num);
bool		is_P_on_plane(t_scene *scene, t_vect3d P, int num);
bool		cast_ray_cam_to_space_check_if_hit_pl(t_scene *scene, int num);

// *** VECTOR STUFF *** \\

t_vect3d	add_vectors(t_vect3d vec1, t_vect3d vec2);
t_vect3d 	subtract_vectors(t_vect3d vec1, t_vect3d vec2);
t_vect3d 	multiply_vector(t_vect3d vec1, double factor);
double		dot_product(t_vect3d vec1, t_vect3d vec2);
t_vect3d	normalize_vector(t_vect3d vec1);

// *** COLOUR STUFF *** \\
int			create_rgbt(int r, int g, int b, int t);
int			get_t(int rgbt);
int			get_r(int rgbt);
int			get_g(int rgbt);
int			get_b(int rgbt);
int 		add_shade(double distance, int color);
int 		get_opposite(int color);

#endif
