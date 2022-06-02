#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include <memory.h>
# include "scenes.h"

enum	e_object_type
{
	PLANE,
	CYLINDER,
	SPHERE,
	DISC,
	TORUS,
	LIGHT
};

typedef struct	s_variable
{
	t_vect3d	R;
	t_vect3d	N;
	double		t;
	double		specular;
	double		diffuse;
	double		angle;
	t_ray		ray;
}				t_variable;

typedef struct	s_quatric
{
	double	Rsq;
	double	rsq;
	double	xD;
	double	yD;
	double	zD;
	double	xE;
	double	yE;
	double	zE;
	double	xD2;
	double	yD2;
	double	zD2;
	double	xE2;
	double	yE2;
	double	zE2;
}				t_quatric;


// *** UTILS *** \\

char		*get_next_line(int fd);
void		hook(void *param);
void		read_scene(t_scene *scene, char *name);
void		loop_pixels(t_data *data, t_scene *scene);
int			find_smallest(t_scene *scene, double *t, int num, int amount);
double		get_camray_angle(t_scene *scene, t_vect3d *Phit, int *num);

// *** RAY STUFF *** \\

t_ray		get_ray(t_scene *scene, t_data *data, double x, double y);
void		transform_ray(t_scene *scene, t_ray *ray, int *num, double z_m[2]);
void		translate_ray(t_vect3d *eye, t_matrix44d I_T);
void		rotate_ray(t_ray *ray, t_matrix44d I_R);
void		rotate_normal(t_vect3d *N, t_matrix44d I_R);

// *** SPHERE STUFF *** \\

int 		find_hit_sphere(t_scene *scene, t_ray *ray, int count, double *close_t);
double		get_sp_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);

// *** PLANE STUFF *** \\

double		find_hit_pl(t_scene *scene, t_ray *ray, int *num);
double		get_pl_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);
int			check_if_plane_between_cam_and_light(t_scene *scene, t_vect3d Phit[2]);

// *** COLOUR STUFF *** \\

int    		hsl_to_rgb(t_vect3d hsl);
double		get_saturation(double l, double minmax[2]);
double 		get_hue(double minmax[2], double r, double g, double b);
int     	check_shadow(t_ray ray, t_scene *scene);
int    		calculate_light(t_vect3d hsl, t_scene *scene);

// *** CYLINDER STUFF *** \\\

double		find_hit_cy(t_scene *scene, t_ray *ray, int *num, int cap, int x, int y);
double		calc_t_0_1(t_scene *scene, t_ray *ray, int *num, double t[4]);
double		find_intersect(t_ray *ray, t_cy_data cy, int *num, int cap);
double		find_intersect_cap(t_ray *ray, t_cy_data cy, int *num, int cap);
bool		t_closest(double t1, double t2, double z_m[2], double z);
double		get_cy_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);
bool		inside_cylinder(t_scene *scene);

// *** DISC STUFF *** \\\

double		find_hit_disc(t_scene *scene, t_ray *ray, int *num);
double		get_di_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);

// *** TORUS STUFF *** \\\

double		find_hit_torus(t_scene *scene, t_ray *ray, int *num, int set_N);
double		get_tor_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);
void		set_i_r_tor(t_scene *scene, int num);
void		set_i_t_tor(t_scene *scene, int num);
void		set_r_tor(t_scene *scene, int num);

#endif
