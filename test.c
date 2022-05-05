#include "inc/miniRT.h"

bool	incr(int *num)
{
	*num = *num + 1;
	return true;
}

int main(void)
{

	int num;
	int num2;

	num = 0;
	num2 = 0;
	if (incr(&num) && num == num2)
		printf("1\n");

	return 0;
}

//gcc test.c src/vectorstuff.c MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/Users/bhoitzin/.brew/opt/glfw/lib/" -I./inc && ./a.out