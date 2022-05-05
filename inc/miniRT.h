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

typedef struct 	s_matrix33d {
	t_vect3d	x;
	t_vect3d	y;
	t_vect3d	z;
}				t_matrix33d;

typedef struct 	s_ray {
	t_vect3d	dir;
	t_vect3d	eye;
}				t_ray;

typedef struct 	s_vec4d {
	double		x;
	double		y;
	double		z;
	double		t;
}				t_vec4d;

typedef struct 	s_matrix44d {
	t_vec4d		x;
	t_vec4d		y;
	t_vec4d		z;
	t_vec4d		t;
}				t_matrix44d;

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
	double		hsl[3];
}				t_pl;

typedef struct s_sp
{
	t_vect3d	C;
    int     	rgb;
	//VECTOR iPV 3 DOUBLES! :))))
	t_vect3d	coord;
	double		size;
	double		hsl[3];
}				t_sp;

typedef struct s_cy
{
	double  x[2];
    double  y[2];
    double  z[2];
	t_vect3d	eye;
	t_vect3d	dir;
    double  diameter;
    double  height;
    int     rgb;
}				t_cy;

typedef struct s_light
{
	double		brightness;
	t_vect3d	ori;
	int			color;
	double		hsl[3];
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
t_ray		calc_ray(t_data *data, t_scene *scene, double x, double y);

// *** GLOBE STUFF \\

void		sphere(t_data *data, t_scene *scene);


// *** PLANE STUFF *** \\

void		draw_plane(t_data *data, t_scene *scene);
int			plane(t_data *data, t_scene *scene);
bool		intersect_eye_plane(t_scene *scene, t_vect3d *vec1, int num);
bool		is_P_on_plane(t_scene *scene, t_vect3d P, int num);
bool		cast_ray_to_space_check_if_hit_pl(t_scene *scene, t_ray *ray, int *num);

// *** VECTOR STUFF *** \\

t_vect3d	add_vectors(t_vect3d vec1, t_vect3d vec2);
t_vect3d 	subtract_vectors(t_vect3d vec1, t_vect3d vec2);
t_vect3d 	multiply_vector(t_vect3d vec1, double factor);
double		dot_product(t_vect3d vec1, t_vect3d vec2);
t_vect3d	normalize_vector(t_vect3d vec1);
t_vect3d 	camera_to_world(t_scene *scene, t_ray ray);
double		magnitude(t_vect3d vec1);
t_vect3d	cross_product(t_vect3d vec1, t_vect3d vec2);
t_matrix44d	set_camera_to_world(t_vect3d from, t_vect3d to);
t_vect3d	divide_vec_scalar(t_vect3d vec1, double s);
t_ray		get_ray(t_scene *scene, t_data *data, double x, double y);
double		distance_two_points(t_vect3d P1, t_vect3d P2);
bool		compare_vectors(t_vect3d vec1, t_vect3d vec2);

// *** COLOUR STUFF *** \\

int			create_rgbt(int r, int g, int b, int t);
int			get_t(int rgbt);
int			get_r(int rgbt);
int			get_g(int rgbt);
int			get_b(int rgbt);
int 		add_shade(double factor, int color);
int 		get_opposite(int color);
int			create_rgb(int r, int g, int b);
int    		hsl_to_rgb(double hsl[3]);
int			light_the_pixel_pl(t_scene *scene, t_ray intersect, int num);
int			light_the_pixel_cy(t_scene *scene, t_ray intersect, int num);

// *** CYLINDER STUFF *** \\\

int			cylinder(t_data *data, t_scene *scene);

#endif
