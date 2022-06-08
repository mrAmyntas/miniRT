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

typedef struct s_variable
{
	t_vect3d	r;
	t_vect3d	n;
	double		t;
	double		specular;
	double		diffuse;
	double		angle;
	t_ray		ray;
}				t_variable;

typedef struct s_quartic
{
	double	r_c2;
	double	r_t2;
	double	xd;
	double	yd;
	double	zd;
	double	xe;
	double	ye;
	double	ze;
	double	xd2;
	double	yd2;
	double	zd2;
	double	xe2;
	double	ye2;
	double	ze2;
}			t_quartic;

// *** UTILS *** 

char	*get_next_line(int fd);
void	hook(void *param);
void	read_scene(t_scene *scene, char *name);
void	loop_pixels(t_data *data, t_scene *scene);
int		find_smallest(double *t, int num, int amount);
double	get_camray_angle(t_scene *scene, t_vect3d *Phit, int *num);
bool	inside_object(t_scene *scene, t_vect3d *Phit, int *num);
double	smallest(double t[3]);
int		check_shadows(t_ray ray, t_scene *scene, double t, t_vect3d *Phit);
double	get_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);
double	find_closest_object(t_scene *scene, t_ray *ray, int *num, int cap);

// *** RAY STUFF *** 

t_ray	get_ray(t_scene *scene, double x, double y);
void	transform_ray(t_scene *scene, t_ray *ray, int *num, double z_m[2]);
void	translate_ray(t_vect3d *eye, t_matrix44d I_T);
void	rotate_ray(t_ray *ray, t_matrix44d I_R);
void	rotate_normal(t_vect3d *N, t_matrix44d I_R);

// *** SPHERE STUFF *** 

int		find_hit_sphere(t_scene *scene, t_ray *ray, int count, double *close_t);
double	get_sp_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);

// *** PLANE STUFF *** 

double	find_hit_pl(t_scene *scene, t_ray *ray, int *num);
double	get_pl_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);
int		check_if_plane_between_cam_and_light(t_scene *scene, t_vect3d Phit[2]);

// *** COLOUR STUFF *** 

t_vect3d	hsl_to_rgb(t_vect3d hsl);
double		get_saturation(double l, double minmax[2]);
double		get_hue(double minmax[2], double r, double g, double b);
int			check_shadow(t_ray ray, t_scene *scene);
int			calculate_light(t_vect3d hsl, t_scene *scene);

// *** CYLINDER STUFF *** 

double	find_hit_cy(t_scene *scene, t_ray *ray, int *num, int cap);
double	calc_t_0_1(t_scene *scene, t_ray *ray, int *num, double t[4]);
double	find_intersect(t_ray *ray, t_cy_data cy, int *num, int cap);
bool	t_closest(double t1, double t2, double z_m[2], double z);
double	get_cy_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);
bool	inside_cylinder(t_scene *scene);
double	find_caps(t_scene *scene, int *num, t_ray *ray, int cap);

// *** DISC STUFF *** 

double	find_hit_disc(t_scene *scene, t_ray *ray, int *num);
double	get_di_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N);

// *** TORUS STUFF *** 

double	find_hit_torus(t_scene *scene, t_ray *ray, int *num, int set_N);
double	get_tor_angle(t_scene *scene, int *num, t_vect3d Phit, t_vect3d *N);
void	set_r_tor(t_scene *scene, int num);
int		get_a(t_scene *scene, t_ray *ray, long double *a, int *num);
int		solve_cubic(t_solve_quartic_var *d);
void	set_normal(t_scene *scene, t_ray *ray, int *num, double t);
void	solve_quartic(t_solve_quartic_var *d);

#endif
