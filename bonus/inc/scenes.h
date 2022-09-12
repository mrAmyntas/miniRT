/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scenes.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/09/11 15:49:09 by bhoitzin      ########   odam.nl         */
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
	double		ks;
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
	t_vect3d	lsh;
	t_matrix44d	i_t;
	t_matrix44d	i_r;
	int			cap;
	int			checker;
}				t_cy;

typedef struct s_tor
{
	t_vect3d	coord;
	t_vect3d	dir;
	double		r_cir;
	double		r_tube;
	t_vect3d	rgb;
	t_vect3d	hsl;
	t_vect3d	lsh;
	t_matrix44d	i_t;
	t_matrix44d	i_r;
	t_matrix44d	r;
	t_vect3d	n;
	int			checker;
}				t_tor;

typedef struct s_pl
{
	t_vect3d	orth_vec;
	t_vect3d	coord;
	t_vect3d	rgb;
	t_vect3d	hsl;
	t_vect3d	lsh;
	int			checker;
}				t_pl;

typedef struct s_di
{
	t_vect3d	orth_vec;
	t_vect3d	coord;
	t_vect3d	rgb;
	t_vect3d	hsl;
	t_vect3d	lsh;
	double		r;
	int			checker;
}				t_di;

typedef struct s_sp
{
	t_vect3d	c;
	t_vect3d	rgb;
	t_vect3d	coord;
	double		size;
	t_vect3d	lsh;
	t_vect3d	hsl;
	int			checker;
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

typedef struct s_solve_quartic
{
	long double			a[5];
	long double			b[3];
	long double			x[3];
	int					ret;
	long double			q1;
	long double			q2;
	long double			p1;
	long double			p2;
	long double			d;
	long double			sqd;
	long double			a2;
	long double			q;
	long double			r;
	long double			r2;
	long double			q3;
	long double			o;
	long double			o2;
	long double			y;
}						t_solve_quartic_var;
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
	t_di		*di;
	t_tor		*tor;
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

enum	e_checkerboard
{
	ON,
	W,
	H
};

// read objects
void		read_cy(t_scene *scene, char **line);
void		read_sp(t_scene *scene, char **line);
void		read_pl(t_scene *scene, char **line);
void		read_di(t_scene *scene, char **line);
void		read_tor(t_scene *scene, char **line);

// read elements
void		read_a(t_scene *scene, char **line);
void		read_c(t_scene *scene, char **line);
void		read_l(t_scene *scene, char **line);

// Utilities
double		ft_atod(char *str);
void		free_strstr(char **str);
int			strstr_len(char **str);
void		create_hsl(t_vect3d *hsl, int r, int g, int b);
int			create_rgb(int r, int g, int b, char *object);
void		ft_error(int num, char *msg);
void		set_i_t(t_vect3d *world_coord, t_matrix44d *mat);
void		set_i_r(t_vect3d *obj_dir, t_matrix44d *mat);

#endif