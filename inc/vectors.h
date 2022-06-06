#ifndef VECTORS_H
# define VECTORS_H
# include "../libft/libft.h"
# include "../mlx42/include/MLX42/MLX42.h"
# include <stdbool.h>

typedef struct s_vect3d {
	double		x;
	double		y;
	double		z;
}				t_vect3d;

typedef struct s_vec4d {
	double		x;
	double		y;
	double		z;
	double		t;
}				t_vec4d;

typedef struct s_matrix33d {
	t_vect3d	x;
	t_vect3d	y;
	t_vect3d	z;
}				t_matrix33d;

typedef struct s_matrix44d {
	t_vec4d		row1;
	t_vec4d		row2;
	t_vec4d		row3;
	t_vec4d		row4;
}				t_matrix44d;

typedef struct s_data {
	mlx_image_t	*mlx_img;
	mlx_t		*mlx;
	int			color;
	double		width;
	double		height;
}				t_data;

t_vect3d	add_vectors(t_vect3d vec1, t_vect3d vec2);
t_vect3d	subtract_vectors(t_vect3d vec1, t_vect3d vec2);
t_vect3d	multiply_vector(t_vect3d vec1, double factor);
double		dot_product(t_vect3d vec1, t_vect3d vec2);
t_vect3d	normalize_vector(t_vect3d vec1);
t_vect3d	cross_product(t_vect3d vec1, t_vect3d vec2);
t_matrix44d	set_camera_to_world(t_vect3d from, t_vect3d to);
t_vect3d	divide_vec_scalar(t_vect3d vec1, double s);
double		distance_two_points(t_vect3d P1, t_vect3d P2);
bool		compare_vectors(t_vect3d vec1, t_vect3d vec2);
t_vec4d		matrix44d_x_vert4d(t_matrix44d matrix, t_vec4d vec);
void		printf_matrix44d(t_matrix44d matrix);
void		printf_vect4d(t_vec4d vec);
t_matrix44d	invert_matrix(t_matrix44d *M);
void		printf_vect3d(t_vect3d vec);
t_matrix44d	matrix_to_translate_to_xyx(t_vect3d C);
bool		comp_d(double x, double y);
double		magnitude(t_vect3d vec);

#endif