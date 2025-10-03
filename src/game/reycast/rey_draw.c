/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rey_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/26 12:00:00 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling(t_game *g, int x, int start)
{
	int		y;
	uint8_t	c[4];

	c[0] = (g->cfg.ceil_color >> 16) & 255;
	c[1] = (g->cfg.ceil_color >> 8) & 255;
	c[2] = g->cfg.ceil_color & 255;
	c[3] = 255;
	y = 0;
	while (y < start)
	{
		put_px_rgba(g->img, x, y, c);
		y++;
	}
}

static void	draw_floor(t_game *g, int x, int start_y)
{
	int		y;
	uint8_t	c[4];

	c[0] = (g->cfg.floor_color >> 16) & 255;
	c[1] = (g->cfg.floor_color >> 8) & 255;
	c[2] = g->cfg.floor_color & 255;
	c[3] = 255;
	y = start_y;
	while (y < WIN_H)
	{
		put_px_rgba(g->img, x, y, c);
		y++;
	}
}

static void	wall_tex_setup(t_game *g, t_ray *r, int tid, t_wslice *ws)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = g->py + r->perp * r->dy;
	else
		wall_x = g->px + r->perp * r->dx;
	wall_x -= floor(wall_x);
	ws->tex_x = (int)(wall_x * (double)g->tex[tid].w);
	if (r->side == 0 && r->dx > 0.0)
		ws->tex_x = g->tex[tid].w - ws->tex_x - 1;
	if (r->side == 1 && r->dy < 0.0)
		ws->tex_x = g->tex[tid].w - ws->tex_x - 1;
	ws->line_h = (int)((double)WIN_H / r->perp);
	ws->step = (double)g->tex[tid].h / (double)ws->line_h;
	ws->tex_pos = 0.0;
	if (ws->line_h > WIN_H)
		ws->tex_pos = (ws->line_h - WIN_H) / 2.0 * ws->step;
}

static void	draw_wall(t_game *g, int x, t_ray *r, t_span sp)
{
	int		y;
	int		tid;
	t_wslice	ws;
	uint8_t	c[4];

	tid = choose_tid(r->side, r->dx, r->dy);
	wall_tex_setup(g, r, tid, &ws);
	y = sp.top;
	while (y <= sp.bot)
	{
		ws.tex_y = (int)ws.tex_pos;
		if (ws.tex_y >= g->tex[tid].h)
			ws.tex_y = g->tex[tid].h - 1;
		if (ws.tex_y < 0)
			ws.tex_y = 0;
		tex_get_rgba(g->tex[tid].img, ws.tex_x, ws.tex_y, c);
		put_px_rgba(g->img, x, y, c);
		ws.tex_pos += ws.step;
		y++;
	}
}

void	draw_column(t_game *g, int x, t_ray *r)
{
	int		line_h;
	t_span	sp;

	if (r->perp < 0.01)
		r->perp = 0.01;
	line_h = (int)((double)WIN_H / r->perp);
	sp.top = -line_h / 2 + WIN_H / 2;
	if (sp.top < 0)
		sp.top = 0;
	sp.bot = line_h / 2 + WIN_H / 2;
	if (sp.bot >= WIN_H)
		sp.bot = WIN_H - 1;
	draw_ceiling(g, x, sp.top);
	if (sp.bot >= sp.top)
		draw_wall(g, x, r, sp);
	draw_floor(g, x, sp.bot + 1);
}
