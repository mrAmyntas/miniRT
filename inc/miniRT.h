/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/24 19:53:41 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/04/21 16:50:02 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct 	s_data {

	mlx_image_t	*mlx_img;
	mlx_t		*mlx;
	int			color;
}				t_data;

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int 	add_shade(double distance, int color);
int 	get_opposite(int color);
void    my_line_put(t_data *data, int x, int y, int color);


#endif
