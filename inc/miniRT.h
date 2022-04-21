/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/24 19:53:41 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/04/21 19:35:57 by mgroen        ########   odam.nl         */
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
# include "../libft/libft.h"

typedef struct 	s_data {

	mlx_image_t	*mlx_img;
	mlx_t		*mlx;
	int			color;
}				t_data;

typedef struct s_scene
{
    int     state[3];
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

char	*get_next_line(int fd);
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int 	add_shade(double distance, int color);
int 	get_opposite(int color);
void    my_line_put(t_data *data, int x, int y, int color);
void    read_scene(t_scene *scene, char *name);

#endif
