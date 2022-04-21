#include "../inc/miniRT.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb & (0xFF << 24)) >> 24);
}

int	get_r(int trgb)
{
	return ((trgb & (0xFF << 16)) >> 16);
}

int	get_g(int trgb)
{
	return ((trgb & (0xFF << 8)) >> 8);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int add_shade(double distance, int color)
{
    int r;
    int b;
    int g;
    int t;

    distance = 1 - distance;
    r = get_r(color);
    r = r * distance;
    b = get_b(color);
    b = b * distance;
    g = get_g(color);
    g = g * distance;
    t = get_t(color);
    color = create_trgb(t, r, g, b);
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
    color = create_trgb(t, r, g, b);
    return (color);
}


void    my_line_put(t_data *data, int x, int y, int color)
{
    while (x < 1920)
    {
        mlx_put_pixel(data->mlx_img, x, y, color);
        x++;
    }
}

