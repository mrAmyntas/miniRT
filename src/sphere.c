#include "../inc/miniRT.h"

double  calc_t0(double b, double c)
{
    double  t[2];

    if ((pow(b, 2) - (4 * c)) < 0)
        return (-1);
    t[0] = (b * -1) + sqrt((pow(b, 2) - (4 * c)));
    t[0] /= 2;
    t[1] = (b * -1) - sqrt((pow(b, 2) - (4 * c)));
    t[1] /= 2;
    if (t[0] <= t[1])
        return (t[0]);
    return (t[1]);
}

void    calc_b_c(t_scene *scene, t_ray ray, double bc[2], int count)
{
    t_vect3d    new;
    t_vect3d    new_D;
    double      power;

    new = subtract_vectors(ray.eye, scene->sp[count].C);
    new_D = multiply_vector(ray.dir, 2);
    bc[0] = dot_product(new, new_D);
    power = pow(new.x, 2) + pow(new.y, 2) + pow(new.z, 2);
    bc[1] = power - pow(scene->sp[count].size / 2, 2);
}

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
        return(create_rgb(hsl.z * 255, hsl.z * 255, hsl.z * 255));
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
    return (create_rgb(rgb[0], rgb[1], rgb[2]));
}

int    calculate_light(double angle, t_vect3d Phit, t_vect3d hsl, t_scene *scene, double t, int shadow)
{
    double  bright[3];

    bright[1] = (1000000 - (t * t)) / 1000000;
    bright[2] = (90 - angle) / 90;
    if (bright[2] < 0)
        bright[2] = 0;
    bright[0] = (bright[1] + bright[2]) / 2 * scene->light->brightness;
    //if (compare_vectors(Phit, Phit) == false)
    //    bright[0] = 0;
    bright[0] = (bright[0] * shadow + scene->a_ratio) / 2;
    if (bright[0] > 1)
        bright[0] = 1;
    hsl.z = bright[0];
    return(hsl_to_rgb(hsl));
}

int     check_shadow(t_ray ray, t_scene *scene)
{
    double  bc[2];
    double  t;
    int     i;

    i = 0;
    while (i < scene->amount[1])
    {
        calc_b_c(scene, ray, bc, i);
        t = calc_t0(bc[0], bc[1]);
        if (t >= 0)
            return (0);
        i++;
    }
    return(1);
}

void    light_to_sp(t_data *data, double  cam_t, t_scene *scene, t_ray ray, int count, int i, int j)
{
    t_vect3d    Phit[2];
    t_vect3d    N;
    double      angle;
    double      bright[3];
    int         rgb;
    double      bc[2];
    double      t;
    int         shadow;

    Phit[0] = add_vectors(ray.eye, multiply_vector(ray.dir, cam_t));
    N = normalize_vector(subtract_vectors(Phit[0], scene->sp[count].C));
    ray.dir = normalize_vector(subtract_vectors(Phit[0], scene->light->ori)); // light direction
    ray.eye = scene->light->ori;
    calc_b_c(scene, ray, bc, count);
    t = calc_t0(bc[0], bc[1]);
    Phit[1] = add_vectors(ray.eye, multiply_vector(ray.dir, t));
    ray.dir = multiply_vector(ray.dir, -1);
    ray.eye = add_vectors(Phit[0], multiply_vector(N, 0.1)); // 0.000001 = bias
    shadow = check_shadow(ray, scene);
    angle = acos(dot_product(N, ray.dir)) / (M_PI / 180);
    mlx_put_pixel(data->mlx_img2, data->width - i, data->height - j, calculate_light(angle, Phit[1], scene->sp[count].hsl, scene, t, shadow));
}

int find_hit_sphere(t_scene *scene, t_ray ray, int count, double *close_t)
{
    double      bc[2];
    double      t;
    int         i;
    int         save_i;

    i = 0;
    *close_t = -1;
    while (i < count)
    {    
        calc_b_c(scene, ray, bc, i);
        t = calc_t0(bc[0], bc[1]);
        if ((t < *close_t && t != -1) || (*close_t < 0 && t != -1))
        {
            *close_t = t;
            save_i = i;
        }
        i++;
    }
    return (save_i);
}

void    sphere(t_data *data, t_scene *scene)
{
    int     i;
    int     j;
    int     count;
    double  t;
    t_ray   ray;

    data->mlx_img2 = mlx_new_image(data->mlx, data->width, data->height);
	memset(data->mlx_img2->pixels, 0, data->mlx_img2->width * data->mlx_img2->height * sizeof(int));   
    i = 0;
    while (i < data->width)
    {
        j = 0;
        while (j < data->height)
        {
            ray = get_ray(scene, data, i, j);
            count = find_hit_sphere(scene, ray, scene->amount[1], &t);
            if (t > -1)
                light_to_sp(data, t, scene, ray, count, i, j);
            j++;
        }
        i++;
    }
    mlx_image_to_window(data->mlx, data->mlx_img2, 0, 0);
}


// D = 3d vector camera
// O = vector startpunt camera
// C = vector middenpunt bol
// R = de helft van size sp
// b = 2 * D * (O - C)
// c = |O - C| ^ 2 - R ^ 2
// a = 1
