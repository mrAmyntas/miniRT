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




void	swap_row(t_vec8d *row1, t_vec8d *row2)
{
	double	tmp;

	tmp = row1->x1;
	row1->x1 = row2->x1;
	row2->x1 = tmp;

	tmp = row1->y1;
	row1->y1 = row2->y1;
	row2->y1 = tmp;

	tmp = row1->z1;
	row1->z1 = row2->z1;
	row2->z1 = tmp;

	tmp = row1->t1;
	row1->t1 = row2->t1;
	row2->t1 = tmp;

	tmp = row1->x2;
	row1->x2 = row2->x2;
	row2->x2 = tmp;

	tmp = row1->y2;
	row1->y2 = row2->y2;
	row2->y2 = tmp;

	tmp = row1->z2;
	row1->z2 = row2->z2;
	row2->z2 = tmp;

	tmp = row1->t2;
	row1->t2 = row2->t2;
	row2->t2 = tmp;

}
