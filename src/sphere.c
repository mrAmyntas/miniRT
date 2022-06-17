#include "../inc/miniRT.h"

// calculates the angle light hits Phit on a sphere
double	get_sp_angle(t_scene *scene, int num[2], t_vect3d Phit, t_vect3d *N)
{
	double		angle;
	t_ray		ray;

    *N = normalize_vector(subtract_vectors(Phit, scene->sp[num[1]].C));
	ray.dir = normalize_vector(subtract_vectors(scene->light[scene->i].ori, Phit));
    angle = acos(dot_product(*N, ray.dir)) * (180 / M_PI);
	return (angle);
}

double  calc_t0(double b, double c)
{
    double  t[2];

    if ((pow(b, 2) - (4 * c)) < 0)
        return (-1);
    t[0] = (b * -1) + sqrt((pow(b, 2) - (4 * c)));
    t[0] /= 2;
    t[1] = (b * -1) - sqrt((pow(b, 2) - (4 * c)));
    t[1] /= 2;
    //printf("%f %f\n", t[0], t[1]);
    if ((t[0] < t[1] && t[0] > 0) || t[1] < 0)
        return (t[0]);
    return (t[1]);
}

void    calc_b_c(t_scene *scene, t_ray *ray, double bc[2], int count)
{
    t_vect3d    new;
    t_vect3d    new_D;
    double      power;

    new = subtract_vectors(ray->eye, scene->sp[count].C);
    new_D = multiply_vector(ray->dir, 2);
    bc[0] = dot_product(new, new_D);
    power = pow(new.x, 2) + pow(new.y, 2) + pow(new.z, 2);
    bc[1] = power - pow(scene->sp[count].size / 2, 2);
}

int	checkers(t_scene *scene, double t, int num)
{
	double		u;
	double		v;
	t_vect3d	phit;

	phit = add_vectors(scene->ray_cam.eye,
			multiply_vector(scene->ray_cam.dir, t));
	phit = subtract_vectors(phit, scene->sp[num].C);
	u = 1 - (atan2(phit.x, phit.z) / (2 * M_PI) + 0.5);
	v = 1 - (acos(phit.y / (scene->sp[num].size / 2)) / M_PI);
	if (!(((int)(u * scene->checkerboard[WIDTH])
			+ (int)(v * scene->checkerboard[HEIGHT])) % 2))
		return (0);
	else
		return (1);
}

double	find_hit_sphere(t_scene *scene, t_ray *ray, int *num, int set)
{
	double		bc[2];
	double		t;
	double		close_t;
	t_vect3d	phit;
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
	if (scene->checkerboard[ON] == true && set == 1 && close_t != -1)
		scene->sp[*num].checker = checkers(scene, close_t, *num);
	return (close_t);
}

//int     check_shadow(t_ray ray, t_scene *scene)
//{
//    double  bc[2];
//    double  t;
//    int     i;
//
//    i = 0;
//    while (i < scene->amount[1])
//    {
//        calc_b_c(scene, ray, bc, i);
//        t = calc_t0(bc[0], bc[1]);
//        if (t >= 0)
//            return (0);
//        i++;
//    }
//    return(1);
//}

//void    light_to_sp(t_data *data, double  cam_t, t_scene *scene, t_ray ray, int count, int i, int j)
//{
//    t_vect3d    Phit[2];
//    t_vect3d    N;
//    double      angle;
//    double      bright[3];
//    int         rgb;
//    double      bc[2];
//    double      t;
//    int         shadow;
//
//    Phit[0] = add_vectors(ray.eye, multiply_vector(ray.dir, cam_t));
//    N = normalize_vector(subtract_vectors(Phit[0], scene->sp[count].C));
//    ray.dir = normalize_vector(subtract_vectors(Phit[0], scene->light->ori)); // light direction
//    ray.eye = scene->light->ori;
//    calc_b_c(scene, ray, bc, count);
//    t = calc_t0(bc[0], bc[1]);
//    Phit[1] = add_vectors(ray.eye, multiply_vector(ray.dir, t));
//    ray.dir = multiply_vector(ray.dir, -1);
//    ray.eye = add_vectors(Phit[0], multiply_vector(N, 0.1)); // 0.000001 = bias
//    shadow = check_shadow(ray, scene);
//    angle = acos(dot_product(N, ray.dir)) / (M_PI / 180);
//    mlx_put_pixel(data->mlx_img2, data->width - i, data->height - j, calculate_light(angle, Phit[1], scene->sp[count].hsl, scene, t, shadow));
//}

//void    sphere(t_data *data, t_scene *scene)
//{
//    int     i;
//    int     j;
//    int     count;
//    double  t;
//    t_ray   ray;
//
//    data->mlx_img2 = mlx_new_image(data->mlx, data->width, data->height);
//	memset(data->mlx_img2->pixels, 0, data->mlx_img2->width * data->mlx_img2->height * sizeof(int));   
//    i = 0;
//    while (i < data->width)
//    {
//        j = 0;
//        while (j < data->height)
//        {
//            ray = get_ray(scene, data, i, j);
//            count = find_hit_sphere(scene, ray, scene->amount[1], &t);
//            if (t > -1)
//                light_to_sp(data, t, scene, ray, count, i, j);
//            j++;
//        }
//        i++;
//    }
//    mlx_image_to_window(data->mlx, data->mlx_img2, 0, 0);
//}


// D = 3d vector camera
// O = vector startpunt camera
// C = vector middenpunt bol
// R = de helft van size sp
// b = 2 * D * (O - C)
// c = |O - C| ^ 2 - R ^ 2
// a = 1
