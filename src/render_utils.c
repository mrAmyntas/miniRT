/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/23 18:50:30 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	inside_object(t_scene *scene, t_vect3d *Phit, int *num)
{
	double	angle;

	angle = get_camray_angle(scene, Phit, num);
	if (angle > 90 || isnan(angle))
		return (true);
	return (false);
}

double	smallest(double t[3])
{
	if ((t[0] < t[1] || t[1] < 0) && (t[0] < t[2] || t[2] < 0) && t[0] > 0)
		return (t[0]);
	else if ((t[1] < t[2] || t[2] < 0) && t[1] > 0)
		return (t[1]);
	else if (t[2] > 0)
		return (t[2]);
	return (-1);
}

// checks if the light ray hits Phit and is not blocked by another object
// t = distance from Phit to light
// t2 = distance from Phit to an object on the ray
int	check_shadows(t_ray ray, t_scene *scene, double t, t_vect3d Phit[2])
{
	double		t2;
	int			num[2];

	if (!check_if_plane_between_cam_and_light(scene, Phit)
		|| !compare_vectors(Phit[0], Phit[1]))
		return (0);
	t2 = find_closest_object(scene, &ray, num, 0);
	if (comp_d(t, t2) && t2 > 0.0)
		return (0);
	return (1);
}

// finds the right function to calculate the angle on Phit
double	get_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double	angle;

	if (num[0] == PLANE)
		angle = get_pl_angle(scene, num, Phit, N);
	else if (num[0] == SPHERE)
		angle = get_sp_angle(scene, num, Phit, N);
	else if (num[0] == CYLINDER)
		angle = get_cy_angle(scene, num, Phit, N);
	else if (num[0] == DISC)
		angle = get_di_angle(scene, num, Phit, N);
	else
		angle = get_tor_angle(scene, num, Phit, N);
	if (isnan(angle))
		angle = -1;
	return (angle);
}
