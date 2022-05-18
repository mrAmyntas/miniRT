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

char		*get_next_line(int fd);
void		hook(void *param);
void		read_scene(t_scene *scene, char *name);
t_ray		calc_ray(t_data *data, t_scene *scene, double x, double y);
void		loop_pixels(t_data *data, t_scene *scene);

// *** VECTOR STUFF *** \\

t_ray		get_ray(t_scene *scene, t_data *data, double x, double y);
t_vect3d 	camera_to_world(t_scene *scene, t_ray ray);
t_matrix44d	get_inverted_R(t_scene *scene, int num);
t_matrix44d	get_inverted_T(t_scene *scene, int num);

// *** SPHERE STUFF *** \\

int 		find_hit_sphere(t_scene *scene, t_ray ray, int count, double *close_t);


// *** PLANE STUFF *** \\

void		draw_plane(t_data *data, t_scene *scene);
int			plane(t_data *data, t_scene *scene);
bool		intersect_eye_plane(t_scene *scene, t_vect3d *vec1, int num);
bool		is_P_on_plane(t_scene *scene, t_vect3d P, int num);
double		cast_ray_to_space_check_if_hit_pl(t_scene *scene, t_ray *ray, int *num);

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
double		cast_ray_to_space_check_if_hit_cy(t_scene *scene, t_ray *ray, int *num);

#endif
