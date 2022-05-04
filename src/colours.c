#include "../inc/miniRT.h"

int	create_rgbt(int r, int g, int b, int t)
{
	return (r << 24 | g << 16 | b << 8 | t);
}

int	get_t(int rgbt)
{
	return (rgbt & 0xFF);
}

int	get_r(int rgbt)
{
	return ((rgbt & (0xFF << 24)) >> 24);
}

int	get_g(int rgbt)
{
	return ((rgbt & (0xFF << 16)) >> 16);
}

int	get_b(int rgbt)
{
	return ((rgbt & (0xFF << 8)) >> 8);
}

int add_shade(double factor, int color)
{
    int r;
    int b;
    int g;
    int t;

//	printf("test\n");
//  factor = 1 - factor;
    r = get_r(color);
    r = r * factor;
    b = get_b(color);
    b = b * factor;
    g = get_g(color);
    g = g * factor;
    t = get_t(color);
    color = create_rgbt(r, g, b, t);
    return (color);
}

int get_opposite(int color)
{
    int r;
    int g;
    int b;
    int t;

    r = 255 - get_r(color);
    b = 255 - get_b(color);
    g = 255 - get_g(color);
    t = get_t(color);
    color = create_rgbt(t, r, g, b);
    return (color);
}


// if (cast_ray_to_space_check_if_hit_pl(scene, &ray, num)) // = hit -> ray now has intersec coords
// 	{
// 		intersect = ray;
// 		//printf("ray.eye: %f %f %f\n", ray.eye.x, ray.eye.y, ray.eye.z);
// 		//cast ray from camera to light, if this hits plane, check if it was BEFORE light
// 		ray.eye = scene->cam->eye;
// 		ray.dir = normalize_vector(subtract_vectors(scene->light->ori, ray.eye));
// 		if (cast_ray_to_space_check_if_hit_pl(scene, &ray, num)) // light hits plane
// 		{
// 			if (distance_two_points(scene->cam->eye, ray.eye) < distance_two_points(scene->cam->eye, scene->light->ori))
// 			{	//from cam -> obj hits first, so light is behind plane
// 				color = add_shade(0.9, data->color);
// 				mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), color);
// 			}
// 			else
// 			{
// //				printf("eye: %f %f %f  ", ray.eye.x, ray.eye.y, ray.eye.z);
// 				tmp = normalize_vector(subtract_vectors(scene->light->ori, intersect.eye));
// 				angle = acos(dot_product(scene->pl->orth_vec, tmp)) / ( M_PI / 180);
// 				distance = distance_two_points(scene->light->ori, intersect.eye);
//         		bright = angle / distance * scene->light->brightness / 40;
// 				if (angle == 0 || bright > 1)
//            			bright = 1;
//        			scene->sp->hsl[2] = bright;
//         		rgb = hsl_to_rgb(scene->sp->hsl);
// //				printf("x:%f y:%f angle:%d\n", x, y, angle);
// 				mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), rgb);
// 			}
// 		}
// 		else
// 		{
// 			printf("eye: %f %f %f  ", ray.eye.x, ray.eye.y, ray.eye.z);
// 			tmp = normalize_vector(subtract_vectors(scene->light->ori, intersect.eye));
// 			angle = acos(dot_product(scene->pl->orth_vec, tmp)) / ( M_PI / 180);
// 			distance = distance_two_points(scene->light->ori, intersect.eye);
//         	bright = angle / distance * scene->light->brightness / 40;
// 			if (angle == 0 || bright > 1)
//         		bright = 1;
//        		scene->sp->hsl[2] = bright;
//         	rgb = hsl_to_rgb(scene->sp->hsl);
// //			printf("x:%f y:%f check:%d\n", x, y, angle);
// 			mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), rgb);
// 		}
// 	}
// }