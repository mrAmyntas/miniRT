#include "../inc/miniRT.h"

int	plane(t_data *data, t_scene *scene)
{
	double x_vector = scene->pl[0].x[1];
	double y_vector = scene->pl[0].y[1];
	double z_vector = scene->pl[0].z[1];

	double x_coord = scene->pl[0].x[0];
	double y_coord = scene->pl[0].y[0];
	double z_coord = scene->pl[0].z[0];

	double c_x_vector = scene->c_x[1];
	double c_y_vector = scene->c_y[1];
	double c_z_vector = scene->c_z[1];

	double c_x_coord = scene->c_x[0];
	double c_y_coord = scene->c_y[0];
	double c_z_coord = scene->c_z[0];


	printf("3d vector pl: [%f,%f,%f]\n", x_vector, y_vector, z_vector);
	printf("coords pl: [%f,%f,%f]\n", x_coord, y_coord, z_coord);

	printf("3d vector cam: [%f,%f,%f]\n", c_x_vector, c_y_vector, c_z_vector);
	printf("coords cam: [%f,%f,%f]\n", c_x_coord, c_y_coord, c_z_coord);

	//intersection camera ray and plane
	double intersect;

	// t = (Q-E) / (D) (?????)
	// Q - E ...
//	double tmp[3];
//	tmp[0] = (x_coord - c_x_coord);
//	tmp[1] = (y_coord - c_y_coord);
//	tmp[2] = (z_coord - c_z_coord);

	double Q = sqrt((x_coord * x_coord) + (y_coord * y_coord) + (z_coord * z_coord));
	double E = sqrt((c_x_coord * c_x_coord) + (c_y_coord * c_y_coord) + (c_z_coord * c_z_coord));
	double D = sqrt((c_x_vector * c_x_vector) + (c_y_vector * c_y_vector) + (c_z_vector * c_z_vector));
	double N = sqrt((x_vector * x_vector) + (y_vector * y_vector) + (z_vector * z_vector));
	double t = (N*(Q-E)) / (N*D);
// intersect = E + tD
	
	if ((N*D) == 0)
		printf("parralellllelol\n");
	if (t < 0)
		printf("no intersect\n");

	intersect = E + t * D;
	printf("intersect: %f\n", intersect);
	return 0;
}
// |v| = |(x, y, z)| = sqrt( x² + y² + z² )


// E = camera coords
// D = camera vector 
// N = plane vector
// Q = plane coord

//A ray is defined by an origin or eye point, E = (x_E, y_E, z_E), and an offset vector, D = (x_D, y_D, z_D). The equation for the ray is:
// P(t) = E + tD	, t>=0
// x(t) = x_E + t * x_D
// y(t) = y_E + t * y_D
// z(t) = z_E + t * z_D

// A plane can be defined by a normal vector, N and a point on the plane, Q.	
// To find the ray/plane intersection :
//
// t = N * (Q-E) / (N * D)
// >>> t = (Q-E) / D ????
// If t<0 then the plane is behind the eye point and there is no intersection. If t>=0 then the intersection point
// is E + tD. If N*D = 0 then the ray is parallel to the plane, and there is no intersection point.




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