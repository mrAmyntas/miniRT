#include "../inc/miniRT.h"

void    draw_line(t_data *data, int x, int ystart, int yend)
{
    mlx_put_pixel(data->mlx_img2, ystart, x, 0xFF0000FF);
    while (ystart < yend)
    {
        ystart++;
        mlx_put_pixel(data->mlx_img2, ystart, x, 0xFF0000FF);
    }
}

void    put_pixels(t_data *data, int x, int y, int xcenter, int ycenter)
{
    int i;

    i = 0;
    while(i < (xcenter - 25))
    {
        mlx_put_pixel(data->mlx_img2, xcenter + x - i, ycenter + y, 0xFF0000FF);
        mlx_put_pixel(data->mlx_img2, xcenter + x - i, ycenter - y, 0xFF0000FF);
        mlx_put_pixel(data->mlx_img2, xcenter + y - i, ycenter + x, 0xFF0000FF);
        mlx_put_pixel(data->mlx_img2, xcenter + y - i, ycenter - x, 0xFF0000FF);
        mlx_put_pixel(data->mlx_img2, xcenter - x + i, ycenter + y, 0xFF0000FF);
        mlx_put_pixel(data->mlx_img2, xcenter - x + i, ycenter - y, 0xFF0000FF);
        mlx_put_pixel(data->mlx_img2, xcenter - y + i, ycenter + x, 0xFF0000FF);
        mlx_put_pixel(data->mlx_img2, xcenter - y + i, ycenter - x, 0xFF0000FF);
        i += 25;
    }
    return;
    mlx_put_pixel(data->mlx_img2, xcenter - x + 10, ycenter + y, 0xFF0000FF);
    mlx_put_pixel(data->mlx_img2, xcenter - x + 10, ycenter - y, 0xFF0000FF);
    mlx_put_pixel(data->mlx_img2, xcenter - y + 10, ycenter + x, 0xFF0000FF);
    mlx_put_pixel(data->mlx_img2, xcenter - y + 10, ycenter - x, 0xFF0000FF);
    mlx_put_pixel(data->mlx_img2, xcenter - x + 20, ycenter + y, 0xFF0000FF);
    mlx_put_pixel(data->mlx_img2, xcenter - x + 20, ycenter - y, 0xFF0000FF);
    mlx_put_pixel(data->mlx_img2, xcenter - y + 20, ycenter + x, 0xFF0000FF);
    mlx_put_pixel(data->mlx_img2, xcenter - y + 20, ycenter - x, 0xFF0000FF);
    return;
    
    draw_line(data, xcenter + x, ycenter - y, ycenter + y);

    draw_line(data, xcenter - x, ycenter - y, ycenter + y);

    draw_line(data, xcenter + y, ycenter - x, ycenter + x);
    
    draw_line(data, xcenter - y, ycenter - x, ycenter + x);
}

void    sphere2(t_data *data, t_scene *scene)
{
    double  r;

    r = pow(scene->sp.x, 2) + pow(scene->sp.y, 2) + pow(scene->sp.z, 2);
}

void    sphere(t_data *data, t_scene *scene)
{
    int xcenter;
    int ycenter;
    int x;
    int y;
    int p;

    sphere2(data, scene);
    return;

    x = 0;
    y = scene->sp[0].size;
    xcenter = y;
    ycenter = y;
    p = 1 - scene->sp[0].size;
    data->mlx_img2 = mlx_new_image(data->mlx, (y * 2) + 1, (y * 2) + 1);
	memset(data->mlx_img2->pixels, 0, data->mlx_img2->width * data->mlx_img2->height * sizeof(int));
    data->mlx_img = mlx_new_image(data->mlx, 1080, 720);
	memset(data->mlx_img->pixels, 200, data->mlx_img->width * data->mlx_img->height * sizeof(int));
    while (x < y)
    {
        put_pixels(data, x, y, xcenter, ycenter);
        x++;
        if (p < 0)
            p = p + 2 * x + 1;
        else
        {
            y--;
            p = p + 2 * (x - y) + 1;
        }
    }
    mlx_image_to_window(data->mlx, data->mlx_img, 0, 360);
    mlx_image_to_window(data->mlx, data->mlx_img2, 150, 150);
}