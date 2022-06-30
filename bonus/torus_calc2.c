/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   torus_calc2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/30 16:36:17 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"
#define EPSIL 0.0000001

static int	calc_x2(t_solve_quartic_var *d)
{
	d->o = -1.0 * pow(fabsl(d->r) + sqrt(d->r2 - d->q3), 1.0 / 3);
	if (d->r < 0)
		d->o = -d->o;
	if (comp_d(d->o, 0) == true)
		d->o2 = 0;
	else
		d->o2 = d->q / d->o;
	d->b[0] = d->b[0] / 3;
	d->x[0] = (d->o + d->o2) - d->b[0];
	d->x[1] = -0.5 * (d->o + d->o2) - d->b[0];
	d->x[2] = 0.5 * sqrt(3.0) * (d->o - d->o2);
	if (fabsl(d->x[2]) < EPSIL)
	{
		d->x[2] = d->x[1];
		return (2);
	}
	return (1);
}

static int	calc_x(t_solve_quartic_var *d)
{
	d->o = d->r / sqrt(d->q3);
	if (d->o < -1)
		d->o = -1;
	if (d->o > 1)
		d->o = 1;
	d->o = acos(d->o);
	d->b[0] = d->b[0] / 3;
	d->q = -2 * sqrt(d->q);
	d->x[0] = d->q * cos(d->o / 3) - d->b[0];
	d->x[1] = d->q * cos((d->o + (M_PI * 2)) / 3) - d->b[0];
	d->x[2] = d->q * cos((d->o - (M_PI * 2)) / 3) - d->b[0];
	return (3);
}

//solves cubic (finds 3 x values). Highest absolute x
//used to solve quartic.
int	solve_cubic(t_solve_quartic_var *d)
{
	d->a2 = d->b[0] * d->b[0];
	d->q = (d->a2 - 3 * d->b[1]) / 9;
	d->r = (d->b[0] * (2 * d->a2 - 9 * d->b[1]) + 27 * d->b[2]) / 54;
	d->r2 = d->r * d->r;
	d->q3 = d->q * d->q * d->q;
	if (d->r2 < d->q3)
		return (calc_x(d));
	else
		return (calc_x2(d));
}

//finds and sets p_values which can be used to solve final
//quadratics
void	solve_quartic(t_solve_quartic_var *d)
{
	if (fabsl(d->d) < EPSIL)
	{
		d->q1 = d->y * 0.5;
		d->q2 = d->q1;
		d->d = d->a[1] * d->a[1] - 4 * (d->a[2] - d->y);
		if (fabsl(d->d) < EPSIL)
		{
			d->p1 = d->a[1] * 0.5;
			d->p2 = d->p1;
		}
		else
		{
			d->sqd = sqrt(d->d);
			d->p1 = (d->a[1] + d->sqd) * 0.5;
			d->p2 = (d->a[1] - d->sqd) * 0.5;
		}
	}
	else
	{
		d->sqd = sqrt(d->d);
		d->q1 = (d->y + d->sqd) * 0.5;
		d->q2 = (d->y - d->sqd) * 0.5;
		d->p1 = (d->a[1] * d->q1 - d->a[3]) / (d->q1 - d->q2);
		d->p2 = (d->a[3] - d->a[1] * d->q2) / (d->q1 - d->q2);
	}
}
