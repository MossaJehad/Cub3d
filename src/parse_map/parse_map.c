/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:44:48 by marvin            #+#    #+#             */
/*   Updated: 2025/09/07 23:38:34 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	scan_row(t_cfg *cfg, int y)
{
	int		x;
	char	ch;

	x = 0;
	while (x < cfg->map_w)
	{
		ch = cfg->map[y][x];
		if (!is_allowed_char(ch))
			return (FALSE);
		if (is_player(ch))
			mark_player(cfg, x, y);
		x++;
	}
	return (TRUE);
}

int	find_player_and_validate_chars(t_cfg *cfg)
{
	int	y;

	y = 0;
	while (y < cfg->map_h)
	{
		if (!scan_row(cfg, y))
			return (FALSE);
		y++;
	}
	if (cfg->player_count != 1)
	{
		err("Error\nMap must have exactly one player\n");
		return (FALSE);
	}
	return (TRUE);
}
