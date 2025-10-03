/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 02:13:58 by marvin            #+#    #+#             */
/*   Updated: 2025/09/05 02:13:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	push_if_void(t_cfg *c, t_qctx *q, int x, int y)
{
	int	w;
	int	h;

	w = c->map_w;
	h = c->map_h;
	if (x < 0 || y < 0 || x >= w || y >= h)
		return ;
	if (q->vis[y * w + x])
		return ;
	if (!is_void_cell(c, x, y))
		return ;
	q->vis[y * w + x] = 1;
	enqueue(q, x, y);
}

void	seed_edges(t_cfg *c, t_qctx *q)
{
	int	x;
	int	y;
	int	w;

	w = c->map_w;
	y = 0;
	while (y < c->map_h)
	{
		x = 0;
		while (x < c->map_w)
		{
			if (is_edge(c, x, y) && is_void_cell(c, x, y) && !q->vis[y * w + x])
			{
				q->vis[y * w + x] = 1;
				enqueue(q, x, y);
			}
			x++;
		}
		y++;
	}
}

void	expand_neighbors(t_cfg *c, t_qctx *q, int x, int y)
{
	push_if_void(c, q, x, y - 1);
	push_if_void(c, q, x, y + 1);
	push_if_void(c, q, x - 1, y);
	push_if_void(c, q, x + 1, y);
}

int	bfs_mark_outside(t_cfg *c, unsigned char *vis, int *qx, int *qy)
{
	t_qctx	q;
	int		head;
	int		x;
	int		y;

	q.vis = vis;
	q.qx = qx;
	q.qy = qy;
	q.tail = 0;
	seed_edges(c, &q);
	head = 0;
	while (head < q.tail)
	{
		x = q.qx[head];
		y = q.qy[head];
		head++;
		expand_neighbors(c, &q, x, y);
	}
	return (1);
}

int	alloc_bufs(t_fillbuf *b)
{
	b->vis = (unsigned char *)ft_calloc(b->cap, 1);
	if (!b->vis)
	{
		err("Error\nOOM\n");
		return (0);
	}
	b->qx = (int *)malloc(sizeof(int) * b->cap);
	if (!b->qx)
	{
		free(b->vis);
		err("Error\nOOM\n");
		return (0);
	}
	b->qy = (int *)malloc(sizeof(int) * b->cap);
	if (!b->qy)
	{
		free(b->vis);
		free(b->qx);
		err("Error\nOOM\n");
		return (0);
	}
	return (1);
}
