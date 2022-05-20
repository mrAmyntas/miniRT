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
    t_rgb[0] = hue + 0.333;
    if (t_rgb[0] > 1)
        t_rgb[0] -= 1;
    else if (t_rgb[0] < 0)
        t_rgb[0] += 1;
    t_rgb[1] = hue;
    if (t_rgb[1] > 1)
        t_rgb[1] -= 1;
    else if (t_rgb[1] < 0)
        t_rgb[1] += 1;
    t_rgb[2] = hue - 0.333;
    if (t_rgb[2] > 1)
        t_rgb[2] -= 1;
    else if (t_rgb[2] < 0)
        t_rgb[2] += 1;
    rgb[0] = test_t_rgb(temp, t_rgb[0]) * 255;
    rgb[1] = test_t_rgb(temp, t_rgb[1]) * 255;
    rgb[2] = test_t_rgb(temp, t_rgb[2]) * 255;
    return (create_rgb(rgb[0], rgb[1], rgb[2], "converting hsl to rgb 2\n"));
}

int    calculate_light(double angle, t_vect3d hsl, t_scene *scene, double t, int shadow)
{
    double  bright[3];

    bright[1] = (100 - t) / 100;
    bright[2] = (90 - angle) / 90;
    bright[0] = (bright[1] + bright[2]) / 2 * scene->light->brightness;
    // bright[0] is nu diffuse light
    if (bright[0] < 0)
        bright[0] = 0;
    bright[0] = (bright[0] * shadow + (scene->a_ratio * hsl.z)) / 2;
    // bright[0] is nu diffuse light en ambient light
    if (bright[0] > 1)
        bright[0] = 1;
    hsl.z = bright[0];
    return(hsl_to_rgb(hsl));
}

int    calculate_light2(double angle, t_vect3d Phit, t_vect3d hsl, t_scene *scene, double t, int shadow)
{
	hsl.z = (scene->a_ratio * hsl.z / 2);
    return(hsl_to_rgb(hsl));
}