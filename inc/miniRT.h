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
	SPHERE
};

// *** UTILS *** \\

char		*get_next_line(int fd);
void		hook(void *param);
void		read_scene(t_scene *scene, char *name);
void		loop_pixels(t_data *data, t_scene *scene);
double		find_smallest(t_scene *scene, double *t, int *num, int amount);

// *** RAY STUFF *** \\

t_ray		get_ray(t_scene *scene, t_data *data, double x, double y);
void		transform_ray(t_scene *scene, t_ray *ray, int *num, double z_m[2]);

// *** SPHERE STUFF *** \\

int 		find_hit_sphere(t_scene *scene, t_ray ray, int count, double *close_t);


// *** PLANE STUFF *** \\

void		draw_plane(t_data *data, t_scene *scene);
int			plane(t_data *data, t_scene *scene);
double		find_hit_pl(t_scene *scene, t_ray *ray, int *num);

// *** COLOUR STUFF *** \\

int 		add_shade(double factor, int color);
int 		get_opposite(int color);
int			create_rgb(int r, int g, int b);
int    		hsl_to_rgb(t_vect3d hsl);
int			light_the_pixel_pl(t_scene *scene, t_vect3d intersect, int num);
int			light_the_pixel_cy(t_scene *scene, t_vect3d intersect, int num);
double		get_saturation(double l, double minmax[2]);
double 		get_hue(double minmax[2], double r, double g, double b);
int     	check_shadow(t_ray ray, t_scene *scene);
int    		calculate_light(double angle, t_vect3d Phit, t_vect3d hsl, t_scene *scene, double t, int shadow);
int   		calculate_light2(double angle, t_vect3d Phit, t_vect3d hsl, t_scene *scene, double t, int shadow);

// *** CYLINDER STUFF *** \\\

int			cylinder(t_data *data, t_scene *scene);
double		find_hit_cy(t_scene *scene, t_ray *ray, int *num, int cap);
double		calc_t_0_1(t_scene *scene, t_ray *ray, int *num, double t[4]);
double		find_intersect(t_ray *ray, t_cy_data cy, int *num, int cap);
double		find_intersect_cap(t_ray *ray, t_cy_data cy, int *num, int cap);
bool		t_closest(double t1, double t2, double z_m[2], double z);

#endif
