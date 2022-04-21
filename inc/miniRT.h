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
	int			width;
	int			height;
}				t_data;

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
    int     l_rgb;
    t_pl    *pl;
    t_sp    *sp;
    t_cy    *cy;
}				t_scene;

char	*get_next_line(int fd);
int		create_rgbt(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int 	add_shade(double distance, int color);
int 	get_opposite(int color);
void    my_line_put(t_data *data, int x, int y, int color);
int		plane(t_data *data);
void	hook(void *param);
void    read_scene(t_scene *scene, char *name);

#endif
