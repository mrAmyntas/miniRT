/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/09/11 14:11:43 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "../../libft/libft.h"
# include "../../mlx42/include/MLX42/MLX42.h"
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
	int32_t		width;
	int32_t		height;
}				t_data;

t_vect3d	add_vectors(t_vect3d vec1, t_vect3d vec2);
t_vect3d	subtract_vectors(t_vect3d vec1, t_vect3d vec2);
t_vect3d	multiply_vector(t_vect3d vec1, double factor);
double		dot_product(t_vect3d vec1, t_vect3d vec2);
t_vect3d	normalize_vector(t_vect3d vec1);
t_vect3d	cross_product(t_vect3d vec1, t_vect3d vec2);
t_vect3d	divide_vec_scalar(t_vect3d vec1, double s);
double		distance_two_points(t_vect3d P1, t_vect3d P2);
bool		compare_vectors(t_vect3d vec1, t_vect3d vec2);
t_vec4d		matrix44d_x_vert4d(t_matrix44d matrix, t_vec4d vec);
bool		comp_d(double x, double y);
double		magnitude(t_vect3d vec);

#endif