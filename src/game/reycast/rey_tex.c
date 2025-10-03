/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:00:00 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/26 12:00:00 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_px_rgba(mlx_image_t *dst, int x, int y, const uint8_t c[4])
{
	uint8_t	*p;

	if ((unsigned)x >= dst->width || (unsigned)y >= dst->height)
		return ;
	p = &dst->pixels[(y * dst->width + x) * 4];
	p[0] = c[0];
	p[1] = c[1];
	p[2] = c[2];
	p[3] = c[3];
}

void	tex_get_rgba(mlx_image_t *tex, int tx, int ty, uint8_t c[4])
{
	uint8_t	*p;

	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	if (tx >= (int)tex->width)
		tx = tex->width - 1;
	if (ty >= (int)tex->height)
		ty = tex->height - 1;
	p = &tex->pixels[(ty * tex->width + tx) * 4];
	c[0] = p[0];
	c[1] = p[1];
	c[2] = p[2];
	c[3] = p[3];
}
