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
