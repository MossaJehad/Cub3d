/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 02:14:12 by marvin            #+#    #+#             */
/*   Updated: 2025/09/05 02:14:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	touches_void_or_edge(t_cfg *c, int y, int x)
{
	if (y == 0 || y == c->map_h - 1 || x == 0 || x == c->map_w - 1)
		return (TRUE);
	if (c->map[y - 1][x] == ' ' || c->map[y + 1][x] == ' ' || c->map[y][x
		- 1] == ' ' || c->map[y][x + 1] == ' ')
		return (TRUE);
	return (FALSE);
}

int	validate_closed(t_cfg *cfg)
{
	int	y;
	int	x;

	y = 0;
	while (y < cfg->map_h)
	{
		x = 0;
		while (x < cfg->map_w)
		{
			if (cfg->map[y][x] == '0')
			{
				if (touches_void_or_edge(cfg, y, x))
					return (err("Error\nMap not closed by walls\n"), FALSE);
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}

int	is_void_cell(t_cfg *c, int x, int y)
{
	char	ch;

	ch = c->map[y][x];
	return (ch == ' ' || ch == '\t');
}

int	is_edge(t_cfg *c, int x, int y)
{
	return (y == 0 || y == c->map_h - 1 || x == 0 || x == c->map_w - 1);
}

void	enqueue(t_qctx *q, int x, int y)
{
	q->qx[q->tail] = x;
	q->qy[q->tail] = y;
	q->tail++;
}
