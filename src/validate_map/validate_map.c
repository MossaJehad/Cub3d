/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:44:33 by marvin            #+#    #+#             */
/*   Updated: 2025/09/07 23:38:34 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_bufs(t_fillbuf *b)
{
	free(b->vis);
	free(b->qx);
	free(b->qy);
}

void	sweep_and_fill(t_cfg *c, t_fillbuf *b)
{
	int	w;
	int	h;
	int	y;
	int	x;

	w = c->map_w;
	h = c->map_h;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if ((c->map[y][x] == ' ' || c->map[y][x] == '\t') && !b->vis[y * w
				+ x])
				c->map[y][x] = '0';
			x++;
		}
		y++;
	}
}

int	fill_interior_spaces(t_cfg *c)
{
	t_fillbuf	b;
	int			w;
	int			h;
	int			ok;
	int			cap;

	w = c->map_w;
	h = c->map_h;
	cap = w * h;
	b.cap = cap;
	ok = alloc_bufs(&b);
	if (!ok)
		return (0);
	ok = bfs_mark_outside(c, b.vis, b.qx, b.qy);
	if (!ok)
	{
		free_bufs(&b);
		return (0);
	}
	sweep_and_fill(c, &b);
	free_bufs(&b);
	return (1);
}
