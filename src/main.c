/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:03:30 by marvin            #+#    #+#             */
/*   Updated: 2025/09/12 03:30:13 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_cfg(t_cfg *c)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		c->tex[i] = NULL;
		c->has_tex[i++] = 0;
	}
	c->floor_color = 0;
	c->ceil_color = 0;
	c->has_floor = 0;
	c->has_ceil = 0;
	c->lines.data = NULL;
	c->lines.size = 0;
	c->lines.cap = 0;
	c->map = NULL;
	c->map_w = 0;
	c->map_h = 0;
	c->player_x = -1;
	c->player_y = -1;
	c->player_dir = 0;
	c->player_count = 0;
}

int	main(int ac, char **av)
{
	t_cfg	cfg;

	if (ac != 2)
		return (err("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	init_cfg(&cfg);
	if (!parse_file(av[1], &cfg))
		return (free_cfg(&cfg), 1);
	if (game_run(&cfg))
	{
		free_cfg(&cfg);
		return (1);
	}
	free_cfg(&cfg);
	return (0);
}
