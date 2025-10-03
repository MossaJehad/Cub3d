/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 03:33:29 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/12 03:33:37 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	map_at(t_cfg *c, int mx, int my)
{
	if (my < 0 || my >= c->map_h || mx < 0 || mx >= c->map_w)
		return (1);
	return (c->map[my][mx] == '1');
}

void	move_forward(t_game *g, double s)
{
	double	nx;
	double	ny;

	nx = g->px + g->dirx * s;
	ny = g->py + g->diry * s;
	if (!map_at(&g->cfg, (int)nx, (int)g->py))
		g->px = nx;
	if (!map_at(&g->cfg, (int)g->px, (int)ny))
		g->py = ny;
}

void	strafe(t_game *g, double s)
{
	double	nx;
	double	ny;

	nx = g->px + (-g->diry) * s;
	ny = g->py + (g->dirx) * s;
	if (!map_at(&g->cfg, (int)nx, (int)g->py))
		g->px = nx;
	if (!map_at(&g->cfg, (int)g->px, (int)ny))
		g->py = ny;
}

void	rotate_player(t_game *g, double a)
{
	double	odx;
	double	opx;

	odx = g->dirx;
	opx = g->planex;
	g->dirx = g->dirx * cos(a) - g->diry * sin(a);
	g->diry = odx * sin(a) + g->diry * cos(a);
	g->planex = g->planex * cos(a) - g->planey * sin(a);
	g->planey = opx * sin(a) + g->planey * cos(a);
}
