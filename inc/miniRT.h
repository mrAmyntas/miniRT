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

typedef struct 	s_vec8d {
	double		x1;
	double		y1;
	double		z1;
	double		t1;
	double		x2;
	double		y2;
	double		z2;
	double		t2;
}				t_vec8d;

typedef struct 	s_matrix44d {
	t_vec4d		row1;
	t_vec4d		row2;
	t_vec4d		row3;
	t_vec4d		row4;
}				t_matrix44d;

typedef struct 	s_matrix48d {
	t_vec8d		row1;
	t_vec8d		row2;
	t_vec8d		row3;
	t_vec8d		row4;
}	
			t_matrix48d;

typedef struct s_matrices
{
	t_matrix44d T;
	t_matrix44d I_T;
	t_matrix48d D;
	t_vec4d		ori_p;
	t_vec4d		t_p;
	double		**M;
	double		**IM;
}				t_matrices;

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

typedef struct s_cy
{
	t_vect3d	eye;
	t_vect3d	dir;
    double  	diameter;
    double  	height;
    int     	rgb;
	t_vect3d	hsl; // h = x = 0, s = y = 1, l = z = 2
}				t_cy;

typedef struct s_light
{
	double		brightness;
	t_vect3d	ori;
	int			color;
}				t_light;

enum	e_object_type
{
	PLANE,
	CYLINDER,
	SPHERE
};


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

char		*get_next_line(int fd);
void		hook(void *param);
void		read_scene(t_scene *scene, char *name);
void		ft_error(int num, char *msg);
t_ray		calc_ray(t_data *data, t_scene *scene, double x, double y);
void		positions_my_lasers(t_data *data, t_scene *scene);

// *** SPHERE STUFF \\

void		sphere(t_data *data, t_scene *scene);
int 		find_hit_sphere(t_scene *scene, t_ray ray, int count, double *close_t);
double 		find_hit_sphere2(t_scene *scene, t_ray ray, int count, int *num);


// *** PLANE STUFF *** \\

void		draw_plane(t_data *data, t_scene *scene);
int			plane(t_data *data, t_scene *scene);
bool		intersect_eye_plane(t_scene *scene, t_vect3d *vec1, int num);
bool		is_P_on_plane(t_scene *scene, t_vect3d P, int num);
double		cast_ray_to_space_check_if_hit_pl(t_scene *scene, t_ray *ray, int *num);

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
t_vec4d 	matrix44d_x_vert4d(t_matrix44d matrix, t_vec4d vec);
void		printf_matrix44d(t_matrix44d matrix);
void		printf_vect4d(t_vec4d vec);
t_matrix44d invert_matrix(t_matrix44d *M);
void		printf_matrix48d(t_matrix48d matrix);
t_matrix44d	get_inverted_T(t_scene *scene, int num);
void		printf_vect3d(t_vect3d vec);
t_matrix44d	get_inverted_R(t_scene *scene, int num);
t_matrix44d	matrix_to_translate_to_xyx(t_vect3d C);
bool		comp_d(double x, double y);

// *** COLOUR STUFF *** \\

int			create_rgbt(int r, int g, int b, int t);
int			get_t(int rgbt);
int			get_r(int rgbt);
int			get_g(int rgbt);
int			get_b(int rgbt);
int 		add_shade(double factor, int color);
int 		get_opposite(int color);
int			create_rgb(int r, int g, int b);
int    		hsl_to_rgb(t_vect3d hsl);
int			light_the_pixel_pl(t_scene *scene, t_vect3d intersect, int num);
int			light_the_pixel_cy(t_scene *scene, t_vect3d intersect, int num);
double		get_saturation(double l, double minmax[2]);
double 		get_hue(double minmax[2], double r, double g, double b);
double		get_min(int r, int g, int b);
double		get_max(int r, int g, int b);
int     	check_shadow(t_ray ray, t_scene *scene);
int    		calculate_light(double angle, t_vect3d Phit, t_vect3d hsl, t_scene *scene, double t, int shadow);

// *** CYLINDER STUFF *** \\\

int			cylinder(t_data *data, t_scene *scene);
double		cast_ray_to_space_check_if_hit_cy(t_scene *scene, t_ray *ray, int *num);

#endif
