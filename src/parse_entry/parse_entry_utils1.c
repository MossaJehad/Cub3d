/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:27:33 by marvin            #+#    #+#             */
/*   Updated: 2025/09/04 20:27:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	all_identifiers_ready(t_cfg *c)
{
	int	i;

	if (!c->has_floor || !c->has_ceil)
		return (FALSE);
	i = 0;
	while (i < 4)
	{
		if (!c->has_tex[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

size_t	compute_seg_len(const char *ct, size_t i, size_t j)
{
	size_t	len;

	len = j - i;
	if (j > i && ct[j - 1] == '\r')
		len = j - i - 1;
	return (len);
}

char	*dup_segment(const char *ct, size_t i, size_t len)
{
	char	*line;

	line = (char *)malloc(len + 1);
	if (!line)
	{
		err("Error\nOOM\n");
		return (NULL);
	}
	if (len > 0)
		ft_memcpy(line, ct + i, len);
	line[len] = '\0';
	return (line);
}

int	process_pre_map_line(char *line, t_cfg *cfg, int *in_map)
{
	if (is_space_line(line))
		return (TRUE);
	if (parse_id_line(line, cfg))
		return (TRUE);
	if (is_map_line(line))
	{
		*in_map = 1;
		if (!push_map_line(cfg, line))
			return (FALSE);
		return (TRUE);
	}
	err("Error\nInvalid line before map\n");
	return (FALSE);
}

int	process_map_line(char *line, t_cfg *cfg)
{
	if (is_space_line(line))
	{
		err("Error\nEmpty line inside map\n");
		return (FALSE);
	}
	if (!push_map_line(cfg, line))
		return (FALSE);
	return (TRUE);
}
