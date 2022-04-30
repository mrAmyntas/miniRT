#include "../inc/miniRT.h"

// t_ray	calc_ray(t_data *data, t_scene *scene, double x, double y)
// {
// 	t_ray	ray;

// 	ray.eye.x = (2 * ((x + 0.5) / data->width) - 1) * (data->width / data->height) * tan(scene->c_fov * M_PI / 180 / 2);
// 	ray.eye.y = (1 - 2 * ((y + 0.5) / data->height)) * tan(scene->c_fov * M_PI / 180 / 2);	
// 	ray.eye.z = -1;

// 	ray.dir = normalize_vector(subtract_vectors(ray.eye, scene->origin));
// 	scene->current_dir = normalize_vector(subtract_vectors(ray.eye, scene->origin));
// 	return (ray);
// }
void calc_hit(t_data *data, t_scene *scene, double x, double y, int num)
{
	t_ray		ray;
	//t_matrix44d	camToWorld;

	//ray = calc_ray(data, scene, x, y); //ray with eye as a pixel point and direction as origin->pixelpoint
	//printf("ray.dir: %f %f %f   ray.eye: %f %f %f     ", ray.dir.x, ray.dir.y, ray.dir.z, ray.eye.x, ray.eye.y, ray.eye.z);
	
	//ray.eye = scene->cam->eye; //sets ray.eye to camera eye, its now 
	//camToWorld = set_camera_to_world(scene->cam->eye, ray.eye);
	//ray.dir = camera_to_world(scene, ray); //camera-to-world translation, sets new direction
	//ray.dir = normalize_vector(ray.dir); //normalize

	ray = get_ray(scene, data, x, y);
	//FIRE MY LASERS
	if (cast_ray_cam_to_space_check_if_hit_pl(scene, ray, num)) // = hit
	{
		mlx_put_pixel(data->mlx_img, (data->width - x), (data->height - y), data->color);
	}
}

void	draw_plane(t_data *data, t_scene *scene, int num)
{
	int	i;
	int	j;

	data->color = scene->pl[0].rgb;
	i = 0;
	while (i < data->width + 1)
	{
		j = 0;
		while (j < data->height + 1)
		{
			calc_hit(data, scene, i, j, num);
			j++;
		}
		i++;
	}
}

int	plane(t_data *data, t_scene *scene)
{
	int	i;

	data->mlx_img = mlx_new_image(data->mlx, data->width + 10, data->height + 10);
	i = 0;
	while (i < scene->amount[0])
	{
		draw_plane(data, scene, i);
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, -1, -1);
	return 0;
}



// Orthogonal matrices have a few interesting properties but maybe the most useful one in Computer Graphics, 
// is that the transpose of an orthogonal matrix is equal to its inverse. Assuming Q is an orthogonal matrix, we can write:

// Q^T=Q^-1 which entails that QQ^T=I

	// printf("coords check: cam: [%f,%f,%f]\ncoords check: pl:  [%f,%f,%f]\n", scene->cam->coord.x,scene->cam->coord.y,scene->cam->coord.z, scene->pl[num].coord.x,scene->pl[num].coord.y,scene->pl[num].coord.z);
	// printf("vec check: cam: [%f,%f,%f]\nvec check: pl:  [%f,%f,%f]\n", scene->cam->eye.x,scene->cam->eye.y,scene->cam->eye.z, scene->pl[0].orth_vec.x,scene->pl[0].orth_vec.y,scene->pl[0].orth_vec.z);

	// t_vect3d tmp = {12310, 760, 2};
	// if (is_P_on_plane(scene, tmp, num))
	// 	printf("P is on the plane!\n");
	// if (intersect_eye_plane(scene, &tmp, num))
	// {
	// 	printf("intersect:[%f,%f,%f]\n", tmray.eyep.x, tmray.eye.y, tmp.z);
	// }

//scan left->right depending on fov?
//we have a vector for camera direction (scene->cam->dir)
//with fov of x, what is left most?
//distance between camera and viewport: 𝑑=1/𝑡𝑎𝑛(𝜃𝑓𝑜𝑣/2)) ??? find source pls

//t_vect3d right_edge_fov;
//right_edge_pov = cos(scene->pov)

// PixelNDCx= (Pixelx+0.5) / ImageWidth   NDC = normalized device coordinates
// PixelNDCy= (Pixely+0.5)/ ImageHeight

// PixelScreen x = 2 * PixelNDCx − 1
// PixelScreen y = 1 - 2 * PixelNDCy

//The value now varies from 1 to -1 as Pixely varies from 0 to ImageWidth.
//Coordinates expressed in this manner are said to be defined in screen space.

// PixelCamerax = (2 * PixelScreenx − 1) * aspect_ratio
// PixelCameray = (1 − 2 * PixelScreeny)

// |BC| = tan(α / 2)   BC is line from middle of viewport to top (straight line) alpha is fov.
// 1 rad = 180°/π 
// α(degrees) = α(radians) * 180° / π


// PixelCamerax = (2 * PixelScreenx − 1) * aspect_ratio * tan (fov/2)
// PixelCameray = (1 − 2 * PixelScreeny) * tan (fov/2)

/*
int i = 0;
	int j = 0;

	data->mlx = mlx_init(data->width, data->height, "MLX42", true);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->mlx_img = mlx_new_image(data->mlx, data->width, data->height);
	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));

	data->color = create_rgbt(255, 255, 255, 255);//0xFFFFFF;

	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));
	while (i < data->width)
	{
		j = 0;
		while (j < data->height)
		{
			mlx_put_pixel(data->mlx_img, i, j, data->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, 0, 0);
	data->mlx_img = mlx_new_image(data->mlx, 100, 100);
	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));
	data->color = scene->pl[0].rgb;
	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			mlx_put_pixel(data->mlx_img, i, j, data->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, 10, 10);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);*/



	/*    int i = 0;
	int j = 0;

	data->mlx = mlx_init(data->width, data->height, "MLX42", true);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->mlx_img = mlx_new_image(data->mlx, data->width, data->height);
	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));

	data->color = create_rgbt(255, 255, 255, 255);//0xFFFFFF;

	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));
	while (i < data->width)
	{
		j = 0;
		while (j < data->height)
		{
			mlx_put_pixel(data->mlx_img, i, j, data->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, 0, 0);
	data->mlx_img = mlx_new_image(data->mlx, 100, 100);
	memset(data->mlx_img->pixels, 255, data->mlx_img->width * data->mlx_img->height * sizeof(int));
	scene->pl[0].rgb = create_rgbt(255, 0, 0, 255);
	data->color = scene->pl[0].rgb;
	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			mlx_put_pixel(data->mlx_img, i, j, data->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->mlx_img, 10, 10);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);*/


//returns a ray with its eye same as the camera and direction towards the coords x and y
t_ray	get_ray(t_scene *scene, t_data *data, double x, double y)
{
	t_vect3d LookAtPoint;
	t_vect3d viewDir;
	t_vect3d up;
	t_vect3d V;		
	t_vect3d U;		


	up.x = 0;
	up.y = 1;
	up.z = 0;
	// pPOINT SHOULD BE ONE IN 'FRONT'  OF CAMERA, WHICH ISNT ALWAyS z + 1

	LookAtPoint = add_vectors(scene->cam->eye, scene->cam->dir);
	//LookAtPoint = scene->cam->eye;
	//LookAtPoint.z = LookAtPoint.z + 1;// NOW IT ALWAYS LOOKS IN FRONT !!!!
	viewDir = normalize_vector(subtract_vectors(LookAtPoint, scene->cam->eye));
	//viewDir = scene->cam->dir;
	U = cross_product(viewDir, up);
	V = cross_product(U, viewDir);

	U = normalize_vector(U);
	V = normalize_vector(V);

	double viewPlaneHalfWidth= tan(scene->c_fov * M_PI / 180 / 2);
	double aspectRatio = data->height/data->width;
	double viewPlaneHalfHeight = aspectRatio * viewPlaneHalfWidth;
//	t_vect3d viewPlaneBottomLeftPoint = LookAtPoint - V * viewPlaneHalfHeight - U * viewPlaneHalfWidth;
	t_vect3d tmp = subtract_vectors(LookAtPoint, multiply_vector(V, viewPlaneHalfHeight));
	t_vect3d viewPlaneBottomLeftPoint = subtract_vectors(tmp, multiply_vector(U, viewPlaneHalfWidth));
	// xIncVector = (U*2*halfWidth)/xResolution;
	// yIncVector = (V*2*halfHeight)/yResolution;

	tmp = multiply_vector(U, (2 * viewPlaneHalfWidth));
	t_vect3d xIncVector = divide_vec_scalar(tmp, data->width);
	tmp = multiply_vector(V, (2 * viewPlaneHalfHeight));
	t_vect3d yIncVector = divide_vec_scalar(tmp, data->height);

	tmp = add_vectors(viewPlaneBottomLeftPoint, multiply_vector(xIncVector, x));
	t_vect3d ViewPlanePoint = add_vectors(tmp, multiply_vector(yIncVector, y));

	t_ray	ray;

	ray.eye = scene->cam->eye;
	ray.dir = subtract_vectors(ViewPlanePoint, scene->cam->eye);
	return (ray);
}