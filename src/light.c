/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/09/11 14:29:55 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

double	test_t_rgb(double temp[3], double t)
{
	if ((6 * t) < 1)
		return (temp[1] + (temp[0] - temp[1]) * 6 * t);
	else if ((2 * t) < 1)
		return (temp[0]);
	else if ((3 * t) < 2)
		return (temp[1] + (temp[0] - temp[1]) * (0.666 - t) * 6);
	else
		return (temp[1]);
}

double	scale_value(double num)
{
	if (num > 1)
		return (num - 1);
	else if (num < 0)
		return (num + 1);
	else
		return (num);
}

// turn a hsl value into a rgb value
t_vect3d	hsl_to_rgb(t_vect3d hsl)
{
	double		temp[2];
	double		t_rgb[3];
	t_vect3d	rgb;
	double		hue;

	rgb.x = hsl.z * 255;
	rgb.y = hsl.z * 255;
	rgb.z = hsl.z * 255;
	if (!(bool)hsl.y)
		return (rgb);
	temp[0] = hsl.z + hsl.y - (hsl.z * hsl.y);
	if (hsl.z < 0.5)
		temp[0] = hsl.z * (1 + hsl.y);
	temp[1] = (2 * hsl.z) - temp[0];
	hue = hsl.x / 360;
	t_rgb[0] = scale_value(hue + 0.333);
	t_rgb[1] = scale_value(hue);
	t_rgb[2] = scale_value(hue - 0.333);
	rgb.x = test_t_rgb(temp, t_rgb[0]) * 255;
	rgb.y = test_t_rgb(temp, t_rgb[1]) * 255;
	rgb.z = test_t_rgb(temp, t_rgb[2]) * 255;
	return (rgb);
}

// combine the colour strenghts of the light sources
t_vect3d	add_light_colours(double bright, t_vect3d colour,
				t_vect3d hsl, t_scene *scene)
{
	t_vect3d	hsl2;
	int			i;

	i = 0;
	while (i < scene->amount[LIGHT])
	{
		bright += scene->light[i].strength;
		i++;
	}
	colour = add_vectors(colour, hsl_to_rgb(hsl));
	create_hsl(&hsl2, colour.x, colour.y, colour.z);
	hsl2.z = bright + scene->a_ratio + (hsl2.z / 2);
	return (hsl2);
}

// calculate the brightness and colour of the pixel
uint32_t	calculate_light(t_vect3d hsl, t_scene *scene)
{
	t_vect3d	colour;
	t_vect3d	hsl2;
	int			bright;

	bright = 0;
	colour.x = 0;
	colour.y = 0;
	colour.z = 0;
	hsl2 = add_light_colours(bright, colour, hsl, scene);
	hsl2.z /= 2;
	if (hsl2.z > 1)
		hsl2.z = 1;
	colour = hsl_to_rgb(hsl2);
	return (create_rgb(colour.x, colour.y, colour.z,
			"combined colours for pixel\n"));
}
