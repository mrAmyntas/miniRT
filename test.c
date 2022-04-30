#include "inc/miniRT.h"

int main(void)
{
	// mlx_t 		*mlx;
	// mlx_image_t	*img;

	// mlx = mlx_init(1080, 720, "MLX42", true);
	// if (!mlx)
	// 	exit(EXIT_FAILURE);
	// img = mlx_new_image(mlx, 1081, 721);
	// mlx_put_pixel(img, 1080, 720, 10);

	t_vect3d x = {0.5,0.5,1};
	normalize_vector(x);
	printf("%f %f %f\n", x.x, x.y,x.z);
	t_ray cam;

	cam.eye.x = 0;
	cam.eye.y = 0;
	cam.eye.z = 0;

	cam.dir = x;

	t_vect3d Point;

	Point = add_vectors(cam.eye, cam.dir);
	printf("Point: %f %f %f\n", Point.x, Point.y, Point.z);
	return (0);
}

//gcc test.c src/vectorstuff.c MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/Users/bhoitzin/.brew/opt/glfw/lib/" -I./inc