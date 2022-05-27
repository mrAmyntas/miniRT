#ifndef SCENES_H
# define SCENES_H
# include "vectors.h"
# include <math.h>

typedef struct s_light
{
	double		brightness;
	t_vect3d	ori;
	int			color;
	double		Kd;
	double		Ks;
	double		strength;
}				t_light;

typedef struct s_cy
{
	t_vect3d	eye;
	t_vect3d	dir;
    double  	r;
    double  	height;
    int     	rgb;
	t_vect3d	hsl;
	t_matrix44d	I_T;
	t_matrix44d	I_R;
	int			cap;
}				t_cy;

typedef struct s_tor
{
	t_vect3d	coord;
	t_vect3d	dir;
    double  	R_cir;
    double  	r_tube;
    int     	rgb;
	t_vect3d	hsl;
	t_matrix44d	I_T;
	t_matrix44d	I_R;
}				t_tor;

typedef struct s_pl
{
	t_vect3d	orth_vec;
	t_vect3d	coord;
    int			rgb;
	t_vect3d	hsl;
}				t_pl;

typedef struct s_di
{
	t_vect3d	orth_vec;
	t_vect3d	coord;
    int			rgb;
	t_vect3d	hsl;
	double		r;
}				t_di;

typedef struct s_sp
{
	t_vect3d	C;
    int     	rgb;
	t_vect3d	coord;
	double		size;
	t_vect3d	lsh;
	t_vect3d	hsl;
	t_matrix44d	I_T;
}				t_sp;

typedef struct 	s_ray {
	t_vect3d	dir;
	t_vect3d	eye;
}				t_ray;

typedef struct 	s_ray_data {
	t_vect3d	LookAtPoint;
	t_vect3d	viewDir;
	t_vect3d	up;
	t_vect3d	V;		
	t_vect3d	U;
	t_vect3d	tmp;
	t_vect3d 	viewPlaneBottomLeftPoint;
	t_vect3d	xIncVector;
	t_vect3d	yIncVector;
	t_vect3d	ViewPlanePoint;
	double 		viewPlaneHalfWidth;
	double 		aspectRatio;
	double 		viewPlaneHalfHeight;
	t_ray		ray;
}				t_ray_data;

typedef struct 	s_cy_data {
	double 		t[4];
	double 		z[2];
	double 		z_m[2];
	int			ret;
}				t_cy_data;

typedef struct 	s_tor_data {
	double 		t[4];
	int			ret;
}				t_tor_data;

typedef struct s_scene
{
	int			i;
    int     	amount[6];
    int    		state[3];
	double 		a_ratio;
    int    		a_rgb;
	t_vect3d	a_hsl;
    double  	c_fov;
	t_vect3d	current_dir;
	t_ray		*cam;
	t_ray		ray_cam;
    t_pl   		*pl;
    t_sp    	*sp;
    t_cy    	*cy;
    t_di    	*di;
	t_tor		*tor;
	t_light		*light;
	t_vect3d	origin;
	t_vect3d	ori_dir;
	t_ray_data	r;
	int			checker[2];
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
void	read_di(t_scene *scene, char **line);
void	read_tor(t_scene *scene, char **line);

// read elements
void	read_a(t_scene *scene, char **line);
void	read_c(t_scene *scene, char **line);
void	read_l(t_scene *scene, char **line);

// Utilities
double		ft_atod(char *str);
void		free_strstr(char **str);
int	   	 	strstr_len(char **str);
void		create_hsl(t_vect3d *hsl, int r, int g, int b);
int	    	create_rgb(int r, int g, int b, char *object);
void	    ft_error(int num, char *msg);
void		set_i_t(t_scene *scene, int num);
void		set_i_r(t_scene *scene, int num);

#endif