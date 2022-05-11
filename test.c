#include "inc/miniRT.h"

bool	incr(int *num)
{
	*num = *num + 1;
	return true;
}

int main(void)
{

	t_vect3d vec2 = {1, 1, 1};
	t_vect3d vec1 = {0, 0, 0.1};

	printf("%f %f %f\n", vec1.x, vec1.y, vec1.z);

	vec1 = normalize_vector(vec1);
	//vec2 = normalize_vector(vec2);
	printf("%f %f %f\n", vec1.x, vec1.y, vec1.z);

	double dot = dot_product(vec1, vec2);
	double magf = magnitude(vec1) * magnitude(vec2);


//	double angle = acos(dot / magf);
	double angle = acos(dot_product(vec1, vec2) / (magnitude(vec1) * magnitude(vec2)));

	printf(":%f\n", angle);
	return 0;
}

//gcc test.c src/vectorstuff.c MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/Users/bhoitzin/.brew/opt/glfw/lib/" -I./inc && ./a.out


