#include "../inc/miniRT.h"

double  test_t_rgb(double temp[3], double t)
{
    if ((6 * t) < 1)
        return(temp[1] + (temp[0] - temp[1]) * 6 * t);
    else if ((2 * t) < 1)
        return(temp[0]);
    else if ((3 * t) < 2)
        return(temp[1] + (temp[0] - temp[1]) * (0.666 - t) * 6);
    else
        return(temp[1]);
}

double  scale_value(double num)
{
    if (num > 1)
        return (num - 1);
    else if (num < 0)
        return (num + 1);
    else
        return (num);
}

int     hsl_to_rgb(t_vect3d hsl)
{
    double  temp[2];
    double  t_rgb[3];
    int     rgb[3];
    double  hue;

    if (!hsl.y)
        return(create_rgb(hsl.z * 255, hsl.z * 255, hsl.z * 255, "converting hsl to rgb\n"));
    temp[0] = hsl.z + hsl.y - (hsl.z * hsl.y);
    if (hsl.z < 0.5)
        temp[0] = hsl.z * (1 + hsl.y);
    temp[1] = (2 * hsl.z) - temp[0];
    hue = hsl.x / 360;
    t_rgb[0] = scale_value(hue + 0.333);
    t_rgb[1] = scale_value(hue);
    t_rgb[2] = scale_value(hue - 0.333);
    rgb[0] = test_t_rgb(temp, t_rgb[0]) * 255;
    rgb[1] = test_t_rgb(temp, t_rgb[1]) * 255;
    rgb[2] = test_t_rgb(temp, t_rgb[2]) * 255;
    return (create_rgb(rgb[0], rgb[1], rgb[2], "converting hsl to rgb 2\n"));
}

int    calculate_light(t_vect3d hsl, t_scene *scene)
{
    double  bright;
    int     i;

    i = 0;
    bright = 0;
    while (i < scene->amount[LIGHT])
    {
        bright += scene->light[i].strength;
        i++;
    }
    hsl.z = bright + scene->a_ratio + (hsl.z / 2); // zoiets???
    // printf("%f %f %f\n", hsl.z, bright, scene->a_ratio);
	if (hsl.z > 1)
		hsl.z = 1;
    return (hsl_to_rgb(hsl));
}
