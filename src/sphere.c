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
    {
        return(create_rgb(hsl.z * 255, hsl.z * 255, hsl.z * 255));
    }
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
    else if (t_rgb[0] < 0)
        t_rgb[2] += 1;    
    rgb[0] = test_t_rgb(temp, t_rgb[0]) * 255;
    rgb[1] = test_t_rgb(temp, t_rgb[1]) * 255;
    rgb[2] = test_t_rgb(temp, t_rgb[2]) * 255;
    return (create_rgb(rgb[0], rgb[1], rgb[2]));
}

void    sphere2(t_data *data, t_scene *scene, int i, int j, int count)
{
    t_vect3d    Phit[2];
    t_vect3d    N;
	t_ray		ray;
    double      bc[2];
    double      t[2];
    double      angle;

    double      bright;
    int         rgb;

    ray = get_ray(scene, data, i, j); //deze toegevoegd als het goed is pakt hij de juiste ray voor de camera afhankelijk van i en j
    ray.dir = normalize_vector(ray.dir);
	// dus dan is ray.eye de positie van de camera en ray.dir de direction naar de pixil i,j.
    calc_b_c(scene, ray, bc, count);
    // calculate t
    t[0] = calc_t0(bc[0], bc[1]);
    if (t[0] != -1)
    {
        Phit[0] = add_vectors(ray.eye, multiply_vector(ray.dir, t[0]));
        printf("%f %f %f\n", Phit[0].x, Phit[0].y, Phit[0].z);
        N = normalize_vector(subtract_vectors(Phit[0], scene->sp[count].C));
        ray.dir = normalize_vector(subtract_vectors(Phit[0], scene->light->ori)); // light direction
        ray.eye = scene->light->ori;
        calc_b_c(scene, ray, bc, count);
        Phit[1] = add_vectors(ray.eye, multiply_vector(ray.dir, t[1]));
        ray.dir = multiply_vector(ray.dir, -1);
        angle = acos(dot_product(N, ray.dir)) / (M_PI / 180);
        t[1] = calc_t0(bc[0], bc[1]);
      	bright = ((t[1] / (angle / 20)) * scene->light->brightness) / 25;
        if (compare_vectors(Phit[0], Phit[1]) == false)
            bright = 0;
        printf("%f %f, %f %f %f\n\n", (1000000 - (t[1] * t[1])) / 1000000, (90 - angle) / 90, Phit[1].x, Phit[1].y, Phit[1].z);
        if (angle == 0)
            bright = 1;
        if (bright > 1)
            bright = 1;
		if (bright < 0)
            bright = 0;
        scene->sp->hsl.z = bright;
        rgb = hsl_to_rgb(scene->sp->hsl);

        mlx_put_pixel(data->mlx_img2, data->width - i, data->height - j, rgb);
    }
}

void    sphere(t_data *data, t_scene *scene)
{
    int i;
    int j;
    int count;

    count = 0;
    data->mlx_img2 = mlx_new_image(data->mlx, data->width, data->height);
	memset(data->mlx_img2->pixels, 0, data->mlx_img2->width * data->mlx_img2->height * sizeof(int));
    while (count < scene->amount[1])
    {    
        i = 0;
        while (i < data->width)
        {
            j = 0;
            while (j < data->height)
            {
                mlx_put_pixel(data->mlx_img2, data->width - i - 1, data->height - j - 1, 0x000000FF);
                sphere2(data, scene, i, j, count);
                j++;
            }
            i++;
        }
        count++;
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

// voor B: tussen | | subtract_vectors, daarna dot_product, - R ^ 2
