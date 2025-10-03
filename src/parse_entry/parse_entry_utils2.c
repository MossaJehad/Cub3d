/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:32:03 by marvin            #+#    #+#             */
/*   Updated: 2025/09/04 20:32:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

size_t	find_line_end(const char *ct, size_t i)
{
	size_t	j;

	j = i;
	while (ct[j] && ct[j] != '\n')
		j++;
	return (j);
}

int	handle_segment(const char *ct, t_segpos pos, t_cfg *cfg, int *in_map)
{
	size_t	len;
	char	*line;

	len = compute_seg_len(ct, pos.i, pos.j);
	line = dup_segment(ct, pos.i, len);
	if (!line)
		return (FALSE);
	if (!*in_map && !process_pre_map_line(line, cfg, in_map))
	{
		free(line);
		return (FALSE);
	}
	if (*in_map && !process_map_line(line, cfg))
	{
		free(line);
		return (FALSE);
	}
	free(line);
	return (TRUE);
}

size_t	advance_index(const char *ct, size_t j)
{
	if (ct[j] == '\n')
		return (j + 1);
	return (j);
}

int	parse_content(const char *ct, t_cfg *cfg)
{
	t_segpos	pos;
	size_t		i;
	int			in_map;

	in_map = 0;
	i = 0;
	while (ct[i])
	{
		pos.i = i;
		pos.j = find_line_end(ct, i);
		if (!handle_segment(ct, pos, cfg, &in_map))
			return (FALSE);
		i = advance_index(ct, pos.j);
	}
	return (TRUE);
}

int	post_parse_validate_and_build(t_cfg *cfg)
{
	if (!all_identifiers_ready(cfg))
	{
		err("Error\nMissing identifiers (NO/SO/WE/EA/F/C)\n");
		return (FALSE);
	}
	if (cfg->lines.size == 0)
	{
		err("Error\nMissing map\n");
		return (FALSE);
	}
	if (!build_rect_map(cfg))
		return (FALSE);
	if (!find_player_and_validate_chars(cfg))
		return (FALSE);
	if (!fill_interior_spaces(cfg))
		return (FALSE);
	if (!validate_closed(cfg))
		return (FALSE);
	return (TRUE);
}
