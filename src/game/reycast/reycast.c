/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 03:31:29 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/26 12:00:00 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	make_ray(t_game *g, int x, t_ray *r)
{
	double	cam_x;

	cam_x = 2.0 * x / (double)WIN_W - 1.0;
	r->dx = g->dirx + g->planex * cam_x;
	r->dy = g->diry + g->planey * cam_x;
	r->side = 0;
	r->perp = 0.0;
}

void	draw_frame(t_game *g)
{
	int		x;
	int		sx;
	int		sy;
	t_ray	r;

	x = 0;
	while (x < WIN_W)
	{
		make_ray(g, x, &r);
		r.perp = cast_one(g, &r, &sx, &sy);
		draw_column(g, x, &r);
		x++;
	}
}
