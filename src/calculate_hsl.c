#include "../inc/vectors.h"

double	get_max(int r, int g, int b)
{
	double	num[3];

	num[0] = r;
	num[0] /= 255;
	num[1] = g;
	num[1] /= 255;
	num[2] = b;
	num[2] /= 255;

	if ((num[0] > num[1] && num[0] > num[2]) || (num[0] == num[1] && num[0] > num[2]) || (num[0] == num[2] && num[0] > num[1]))
		return(num[0]);
	else if ((num[1] > num[0] && num[1] > num[2]) || (num[1] == num[0] && num[1] > num[2]) || (num[1] == num[2] && num[1] > num[0]))
		return(num[1]);
	else if ((num[2] > num[0] && num[2] > num[1]) || (num[2] == num[0] && num[2] > num[1]) || (num[2] == num[1] && num[2] > num[0]))
		return(num[2]);
	return(num[0]);
}

double	get_min(int r, int g, int b)
{
	double	num[3];

	num[0] = r;
	num[0] /= 255;
	num[1] = g;
	num[1] /= 255;
	num[2] = b;
	num[2] /= 255;

	if ((num[0] < num[1] && num[0] < num[2]) || (num[0] == num[1] && num[0] < num[2]) || (num[0] == num[2] && num[0] < num[1]))
		return(num[0]);
	else if ((num[1] < num[0] && num[1] < num[2]) || (num[1] == num[0] && num[1] < num[2]) || (num[1] == num[2] && num[1] < num[0]))
		return(num[1]);
	else if ((num[2] < num[0] && num[2] < num[1]) || (num[2] == num[0] && num[2] < num[1]) || (num[2] == num[1] && num[2] < num[0]))
		return(num[2]);
	return(num[0]);
}

double	get_saturation(double l, double minmax[2])
{
	double	num;

	if (l > 0.5)
		num = (minmax[1] - minmax[0]) / (2 - minmax[1] - minmax[0]);
	else
		num = (minmax[1] - minmax[0]) / (minmax[1] + minmax[0]);
	return (num);
}

double get_hue(double minmax[2], double r, double g, double b)
{
	double	num;
	double	rgb[3];

	rgb[0] = r;
	rgb[0] /= 255;
	rgb[1] = g;
	rgb[1] /= 255;
	rgb[2] = b;
	rgb[2] /= 255;
	if (minmax[1] == rgb[0])
		num = (rgb[1] - rgb[2]) / (minmax[1] - minmax[0]);
	else if (minmax[1] == rgb[1])
		num = 2 + (rgb[2] - rgb[0]) / (minmax[1] - minmax[0]);
	else if (minmax[1] == rgb[2])
		num = 4 + (rgb[0] - rgb[1]) / (minmax[1] - minmax[0]);
	return(num * 60);	
}

void	create_hsl(t_vect3d *hsl, int r, int g, int b)
{
	double	minmax[2];

	minmax[0] = get_min(r, g, b);
	minmax[1] = get_max(r, g, b);
	hsl->z = (minmax[0] + minmax[1]) / 2;
	hsl->y = 0;
	hsl->x = 0;
	if (minmax[0] == minmax[1])
		return;
	hsl->y = get_saturation(hsl->z, minmax);
	hsl->x = get_hue(minmax, r , g , b );
	if (hsl->x < 0)
		hsl->x += 360;
}
