#include "../inc/miniRT.h"

//void    draw_line(t_data *data, t_scene *scene, double y, double x, int set)
//{
//    double  ystart;
//
//    ystart = (scene->sp[0].size - y) - ((scene->sp[0].size / 2 + scene->sp[0].y) * 2);
//    while (ystart <= y)
//    {
//        if (ystart >= 0)
//            mlx_put_pixel(data->mlx_img2, x, ystart, 0xFF0000FF);
//        ystart++;
//    } 
//}
//
//void    sphere3(t_data *data, t_scene *scene)
//{
//    double  x;
//    double  y;
//    int     set;
//
//    data->mlx_img2 = mlx_new_image(data->mlx, 1080, 720);
//	memset(data->mlx_img2->pixels, 0, data->mlx_img2->width * data->mlx_img2->height * sizeof(int));
//    x = scene->sp[0].x - (scene->sp[0].size / 2);
//    while(x <= scene->sp[0].x + (scene->sp[0].size / 2))
//    {
//        set = 1;
//        y = pow(x - scene->sp[0].x, 2) + pow(scene->sp[0].z, 2) - pow((scene->sp[0].size / 2), 2);
//        if (y < 0)
//        {
//            y *= -1;
//            set = -1;
//        }
//        y = sqrt(y);
//        if (x >= 0)
//            draw_line(data, scene, y - scene->sp[0].y, x, set);
//        x++;
//    }
//    mlx_image_to_window(data->mlx, data->mlx_img2, 0, 0);
//}

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

void    sphere2(t_data *data, t_scene *scene, int i, int j)
{
    t_vect3d    C;
    t_vect3d    new;
    t_vect3d    new_D;
    t_vect3d    Phit;

    t_vect3d    current_dir;
	t_ray		ray;

    double      b;
    double      magnitude;
    double      c;
    double      power;
    double      t;
    
    C.x = scene->sp[0].x;
    C.y = scene->sp[0].y;
    C.z = scene->sp[0].z;

    ray = get_ray(scene, data, i, j); //deze toegevoegd als het goed is pakt hij de juiste ray voor de camera afhankelijk van i en j
	// dus dan is ray.eye de positie van de camera en ray.dir de direction naar de pixil i,j.

    // calculate b
    new = subtract_vectors(scene->cam->eye, C);
    new_D = multiply_vector(current_dir, 2);
    b = dot_product(new, new_D);

    // calculate c
    power = pow(new.x, 2) + pow(new.y, 2) + pow(new.z, 2);
    magnitude = sqrt(power);
    c = pow(magnitude, 2) - pow(scene->sp[0].size / 2, 2);

    // calculate t
    t = calc_t0(b, c);
    if (t != -1)
    {
        //printf("hoi\n");
        Phit = add_vectors(scene->cam->eye, multiply_vector(scene->cam->dir, t));
    }
    //mlx_put_pixel(data->mlx_img2, i, j, 0xFF0000FF);
}

void    sphere(t_data *data, t_scene *scene)
{
    int i;
    int j;

    i = 0;
    data->mlx_img2 = mlx_new_image(data->mlx, 1080, 720);
	memset(data->mlx_img2->pixels, 0, data->mlx_img2->width * data->mlx_img2->height * sizeof(int));
    while (i < data->width)
    {
        j = 0;
        while (j < data->height)
        {
            sphere2(data, scene, i, j);
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

// voor B: tussen | | subtract_vectors, daarna dot_product, - R ^ 2
