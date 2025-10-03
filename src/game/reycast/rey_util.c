/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rey_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/26 12:00:00 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	choose_tid(int side, double rdx, double rdy)
{
	if (side == 0)
	{
		if (rdx > 0.0)
			return (TEX_EA);
		return (TEX_WE);
	}
	if (rdy > 0.0)
		return (TEX_SO);
	return (TEX_NO);
}

static void	init_cast(double d[4], int step[2], t_game *g, t_ray *ray)
{
	if (ray->dx == 0.0)
		d[0] = 1e30;
	else
		d[0] = fabs(1.0 / ray->dx);
	if (ray->dy == 0.0)
		d[1] = 1e30;
	else
		d[1] = fabs(1.0 / ray->dy);
	step[0] = (ray->dx > 0.0);
	step[0] = step[0] * 2 - 1;
	step[1] = (ray->dy > 0.0);
	step[1] = step[1] * 2 - 1;
	if (ray->dx > 0.0)
		d[2] = ((int)g->px + 1.0 - g->px) * d[0];
	else
		d[2] = (g->px - (int)g->px) * d[0];
	if (ray->dy > 0.0)
		d[3] = ((int)g->py + 1.0 - g->py) * d[1];
	else
		d[3] = (g->py - (int)g->py) * d[1];
}

static double	cast_traverse(t_game *g, t_ray *ray, double d[4], int step[2])
{
	int	mx;
	int	my;

	mx = (int)g->px;
	my = (int)g->py;
	while (1)
	{
		if (d[2] < d[3])
		{
			d[2] += d[0];
			mx += step[0];
			ray->side = 0;
		}
		else
		{
			d[3] += d[1];
			my += step[1];
			ray->side = 1;
		}
		if (map_at(&g->cfg, mx, my))
			break ;
	}
	if (ray->side == 0)
		return (d[2] - d[0]);
	return (d[3] - d[1]);
}

double	cast_one(t_game *g, t_ray *ray, int *sx, int *sy)
{
	int		step[2];
	double	d[4];
	double	perp;

	init_cast(d, step, g, ray);
	*sx = step[0];
	*sy = step[1];
	perp = cast_traverse(g, ray, d, step);
	return (perp);
}
