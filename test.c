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

	t_vect3d x = {0,0,0};
	t_vect3d y = {0,0,1};

	t_vect3d xy = normalize_vector(subtract_vectors(y, x));
	printf("Point: %f %f %f\n", xy.x, xy.y, xy.z);
	return (0);
}

//gcc test.c src/vectorstuff.c MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/Users/bhoitzin/.brew/opt/glfw/lib/" -I./inc