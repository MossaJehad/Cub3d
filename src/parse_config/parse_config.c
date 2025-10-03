/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:11:33 by marvin            #+#    #+#             */
/*   Updated: 2025/09/04 20:11:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_color_triplet(char *s, int *dst, int *flag)
{
	int	r;
	int	g;
	int	b;

	if (*flag)
	{
		err("Error\nDuplicate color identifier\n");
		return (FALSE);
	}
	if (!read_component(&s, &r))
		return (FALSE);
	if (!expect_comma(&s) || !read_component(&s, &g))
		return (FALSE);
	if (!expect_comma(&s) || !read_component(&s, &b))
		return (FALSE);
	skip_ws(&s);
	if (*s)
	{
		err("Error\nColor needs 3 values\n");
		return (FALSE);
	}
	*dst = (r << 16) | (g << 8) | b;
	*flag = 1;
	return (TRUE);
}

int	parse_id_line(char *line, t_cfg *cfg)
{
	char	*s;

	s = skip_spaces(line);
	if (s[0] == 'N' && s[1] == 'O' && (s[2] == ' ' || s[2] == '\t'))
		return (set_tex(cfg, TEX_NO, s + 2));
	if (s[0] == 'S' && s[1] == 'O' && (s[2] == ' ' || s[2] == '\t'))
		return (set_tex(cfg, TEX_SO, s + 2));
	if (s[0] == 'W' && s[1] == 'E' && (s[2] == ' ' || s[2] == '\t'))
		return (set_tex(cfg, TEX_WE, s + 2));
	if (s[0] == 'E' && s[1] == 'A' && (s[2] == ' ' || s[2] == '\t'))
		return (set_tex(cfg, TEX_EA, s + 2));
	if (s[0] == 'F' && (s[1] == ' ' || s[1] == '\t'))
		return (parse_color_triplet(s + 1, &cfg->floor_color, &cfg->has_floor));
	if (s[0] == 'C' && (s[1] == ' ' || s[1] == '\t'))
		return (parse_color_triplet(s + 1, &cfg->ceil_color, &cfg->has_ceil));
	return (FALSE);
}
