/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scenes.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/09/11 14:30:48 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENES_H
# define SCENES_H
# include "vectors.h"
# include <math.h>

typedef struct s_light
{
	t_vect3d	ori;
	t_vect3d	color;
	t_vect3d	hsl;
	double		kd;
	double		strength;
}				t_light;

typedef struct s_cy
{
	t_vect3d	eye;
	t_vect3d	dir;
	double		r;
	double		height;
	t_vect3d	rgb;
	t_vect3d	hsl;
	t_matrix44d	i_t;
	t_matrix44d	i_r;
	int			cap;
}				t_cy;

typedef struct s_pl
{
	t_vect3d	orth_vec;
	t_vect3d	coord;
	t_vect3d	rgb;
	t_vect3d	hsl;
}				t_pl;

typedef struct s_sp
{
	t_vect3d	c;
	t_vect3d	rgb;
	t_vect3d	coord;
	double		size;
	t_vect3d	hsl;
}				t_sp;

typedef struct s_ray {
	t_vect3d	dir;
	t_vect3d	eye;
}				t_ray;

typedef struct s_ray_data {
	t_vect3d	lookatpoint;
	t_vect3d	viewdir;
	t_vect3d	up;
	t_vect3d	v;		
	t_vect3d	u;
	t_vect3d	tmp;
	t_vect3d	viewplanebottomleftpoint;
	t_vect3d	x_inc_vector;
	t_vect3d	y_inc_vector;
	t_vect3d	viewplanepoint;
	double		viewplanehalfwidth;
	double		aspectratio;
	double		viewplanehalfheight;
	t_ray		ray;
}				t_ray_data;

typedef struct s_cy_data {
	double	t[4];
	double	z[2];
	double	z_m[2];
	double	ret;
}			t_cy_data;

typedef struct s_scene
{
	int			i;
	int			amount[8];
	int			state[3];
	double		a_ratio;
	t_vect3d	a_rgb;
	t_vect3d	a_hsl;
	double		c_fov;
	t_vect3d	current_dir;
	t_ray		*cam;
	t_ray		ray_cam;
	t_pl		*pl;
	t_sp		*sp;
	t_cy		*cy;
	t_light		*light;
	t_vect3d	origin;
	t_vect3d	ori_dir;
	t_ray_data	r;
	int			cb[3];
}				t_scene;

enum	e_cy_cap
{
	NOT,
	BOT,
	TOP
};

// read objects
void	read_cy(t_scene *scene, char **line);
void	read_sp(t_scene *scene, char **line);
void	read_pl(t_scene *scene, char **line);

// read elements
void	read_a(t_scene *scene, char **line);
void	read_c(t_scene *scene, char **line);
void	read_l(t_scene *scene, char **line);

// Utilities
double		ft_atod(char *str);
void		free_strstr(char **str);
int			strstr_len(char **str);
void		create_hsl(t_vect3d *hsl, double r, double g, double b);
uint32_t	create_rgb(double r, double g, double b, char *object);
void		ft_error(int num, char *msg);
void		set_i_t(t_vect3d *world_coord, t_matrix44d *mat);
void		set_i_r(t_vect3d *obj_dir, t_matrix44d *mat);

#endif