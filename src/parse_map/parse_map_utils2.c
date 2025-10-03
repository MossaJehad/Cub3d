/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 02:11:33 by marvin            #+#    #+#             */
/*   Updated: 2025/09/05 02:11:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	copy_and_detab_line(t_cfg *cfg, int i)
{
	int	len;
	int	k;

	len = (int)ft_strlen(cfg->lines.data[i]);
	if (len <= 0)
		return ;
	ft_memcpy(cfg->map[i], cfg->lines.data[i], len);
	k = 0;
	while (k < len)
	{
		if (cfg->map[i][k] == '\t')
			cfg->map[i][k] = ' ';
		k++;
	}
}

int	build_rect_map(t_cfg *cfg)
{
	int	i;
	int	w;

	w = compute_max_w(cfg);
	cfg->map_w = w;
	cfg->map_h = cfg->lines.size;
	if (!alloc_map(cfg, w))
		return (FALSE);
	i = 0;
	while (i < cfg->map_h)
	{
		copy_and_detab_line(cfg, i);
		i++;
	}
	return (TRUE);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_allowed_char(char ch)
{
	if (ch == '0' || ch == '1' || ch == ' ')
		return (TRUE);
	if (is_player(ch))
		return (TRUE);
	err("Error\nInvalid char in map\n");
	return (FALSE);
}

void	mark_player(t_cfg *cfg, int x, int y)
{
	cfg->player_count++;
	cfg->player_x = x;
	cfg->player_y = y;
	cfg->player_dir = cfg->map[y][x];
	cfg->map[y][x] = '0';
}
