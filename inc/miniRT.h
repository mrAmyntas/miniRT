/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/24 19:53:41 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/04/21 16:51:37 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_scene
{
	double  a_ratio;
    int     a_rgb;
    double  c_x[2];
    double  c_y[2];
    double  c_z[2];
    int     c_fov;
    double  l_x;
    double  l_y;
    double  l_z;
    double  l_bright;
}				t_scene;

typedef struct s_pl
{
	double  x[2];
    double  y[2];
    double  z[2];
    int     rgb;
    
}				t_pl;

typedef struct s_sp
{
	double  x;
    double  y;
    double  z;
    double  size;
    int     rgb;
}				t_sp;

typedef struct s_cy
{
	double  x[2];
    double  y[2];
    double  z[2];
    double  diameter;
    double  height;
    int     rgb;
}				t_cy;

#endif
