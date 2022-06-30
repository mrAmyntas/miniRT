/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/30 16:36:13 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"

// calculates the angle light hits Phit on a sphere
double	get_sp_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		angle;
	t_ray		ray;
	t_vect3d	vec;

	*N = normalize_vector(subtract_vectors(Phit, scene->sp[num[1]].c));
	vec = subtract_vectors(scene->light[scene->i].ori, Phit);
	ray.dir = normalize_vector(vec);
	angle = acos(dot_product(*N, ray.dir)) * (180 / M_PI);
	return (angle);
}

// calculates the closest hit on the sphere
double	calc_t0(double b, double c)
{
	double	t[2];

	if ((pow(b, 2) - (4 * c)) < 0)
		return (-1);
	t[0] = (b * -1) + sqrt((pow(b, 2) - (4 * c)));
	t[0] /= 2;
	t[1] = (b * -1) - sqrt((pow(b, 2) - (4 * c)));
	t[1] /= 2;
	if ((t[0] < t[1] && t[0] > 0) || t[1] < 0)
		return (t[0]);
	return (t[1]);
}

// calculates the values b and c
void	calc_b_c(t_scene *scene, t_ray *ray, double bc[2], int count)
{
	t_vect3d	new;
	t_vect3d	new_d;
	double		power;

	new = subtract_vectors(ray->eye, scene->sp[count].c);
	new_d = multiply_vector(ray->dir, 2);
	bc[0] = dot_product(new, new_d);
	power = pow(new.x, 2) + pow(new.y, 2) + pow(new.z, 2);
	bc[1] = power - pow(scene->sp[count].size / 2, 2);
}

// calculates if a point needs to be 
// the opposite colour for a checkerboard pattern
int	checkers(t_scene *scene, double t, int num)
{
	double		u;
	double		v;
	t_vect3d	phit;

	phit = add_vectors(scene->ray_cam.eye,
			multiply_vector(scene->ray_cam.dir, t));
	phit = subtract_vectors(phit, scene->sp[num].c);
	u = 1 - (atan2(phit.x, phit.z) / (2 * M_PI) + 0.5);
	v = 1 - (acos(phit.y / (scene->sp[num].size / 2)) / M_PI);
	if (!(((int)(u * scene->cb[W])
			+ (int)(v * scene->cb[H])) % 2))
		return (0);
	else
		return (1);
}

// calculates the hit point between ray and the closest sphere
double	find_hit_sphere(t_scene *scene, t_ray *ray, int *num, int set)
{
	double		bc[2];
	double		t;
	double		close_t;
	int			i;

	i = 0;
	close_t = -1;
	while (i < scene->amount[SPHERE])
	{
		calc_b_c(scene, ray, bc, i);
		t = calc_t0(bc[0], bc[1]);
		if ((t < close_t && t > 0) || (close_t < 0 && t > 0))
		{
			close_t = t;
			*num = i;
		}
		i++;
	}
	if (scene->cb[ON] == true && set == 1 && close_t != -1)
		scene->sp[*num].checker = checkers(scene, close_t, *num);
	return (close_t);
}
