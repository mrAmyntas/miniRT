/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/24 19:53:41 by bhoitzin      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/04/21 16:51:37 by mgroen        ########   odam.nl         */
=======
/*   Updated: 2022/04/21 16:45:45 by bhoitzin      ########   odam.nl         */
>>>>>>> 4759e93f2683c43b67f68d3fbd97f30397d0e4c1
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
}				t_data;

typedef struct s_scene
{
	double  a_ratio;
    int     a_rgb;
    double  c_x[2];
    double  c_y[2];
    double  c_z[2];
    int     c_fov;
    double  l_x;
    double  l_y;
    double  l_z;
    double  l_bright;
}				t_scene;

typedef struct s_pl
{
	double  x[2];
    double  y[2];
    double  z[2];
    int     rgb;
    
}				t_pl;

typedef struct s_sp
{
	double  x;
    double  y;
    double  z;
    double  size;
    int     rgb;
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

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int 	add_shade(double distance, int color);
int 	get_opposite(int color);
void    my_line_put(t_data *data, int x, int y, int color);

#endif
