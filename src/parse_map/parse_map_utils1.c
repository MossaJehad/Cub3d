/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 02:11:09 by marvin            #+#    #+#             */
/*   Updated: 2025/09/05 02:11:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_map_line(const char *s)
{
	int	i;
	int	ok;

	i = 0;
	ok = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i])
	{
		if (s[i] == '0' || s[i] == '1' || s[i] == 'N' || s[i] == 'S'
			|| s[i] == 'E' || s[i] == 'W' || s[i] == ' ' || s[i] == '\t')
			ok = 1;
		else
			return (FALSE);
		i++;
	}
	return (ok);
}

int	grow_lines(t_cfg *cfg)
{
	char	**nd;
	int		i;

	if (cfg->lines.cap == 0)
		cfg->lines.cap = 8;
	else
		cfg->lines.cap = cfg->lines.cap * 2;
	nd = (char **)ft_calloc(cfg->lines.cap, sizeof(char *));
	if (!nd)
	{
		err("Error\nOOM\n");
		return (FALSE);
	}
	if (cfg->lines.data)
	{
		i = 0;
		while (i < cfg->lines.size)
		{
			nd[i] = cfg->lines.data[i];
			i++;
		}
		free(cfg->lines.data);
	}
	cfg->lines.data = nd;
	return (TRUE);
}

int	push_map_line(t_cfg *cfg, char *line)
{
	char	*dup;

	dup = sdup(line);
	if (!dup)
	{
		err("Error\nOOM\n");
		return (FALSE);
	}
	if (cfg->lines.size + 1 > cfg->lines.cap)
	{
		if (!grow_lines(cfg))
		{
			free(dup);
			return (FALSE);
		}
	}
	cfg->lines.data[cfg->lines.size] = dup;
	cfg->lines.size++;
	return (TRUE);
}

int	compute_max_w(t_cfg *cfg)
{
	int	i;
	int	w;
	int	len;

	i = 0;
	w = 0;
	while (i < cfg->lines.size)
	{
		len = (int)ft_strlen(cfg->lines.data[i]);
		if (len > w)
			w = len;
		i++;
	}
	return (w);
}

int	alloc_map(t_cfg *cfg, int w)
{
	int	i;

	cfg->map = (char **)ft_calloc(cfg->map_h + 1, sizeof(char *));
	if (!cfg->map)
	{
		err("Error\nOOM\n");
		return (FALSE);
	}
	i = 0;
	while (i < cfg->map_h)
	{
		cfg->map[i] = (char *)ft_calloc(w + 1, sizeof(char));
		if (!cfg->map[i])
		{
			err("Error\nOOM\n");
			return (FALSE);
		}
		ft_memset(cfg->map[i], ' ', w);
		i++;
	}
	return (TRUE);
}
