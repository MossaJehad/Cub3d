/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:11:52 by marvin            #+#    #+#             */
/*   Updated: 2025/09/04 20:11:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_texture_path(char *path)
{
	if (!try_open_texture(path))
	{
		free(path);
		err("Error\nTexture path not found\n");
		return (FALSE);
	}
	return (TRUE);
}

int	set_tex(t_cfg *c, int idx, char *s)
{
	char	*path;

	if (c->has_tex[idx])
	{
		err("Error\nDuplicate texture identifier\n");
		return (FALSE);
	}
	path = dup_trimmed_path(s);
	if (!path)
		return (FALSE);
	if (!check_texture_path(path))
		return (FALSE);
	c->tex[idx] = path;
	c->has_tex[idx] = 1;
	return (TRUE);
}

int	parse_int_0_255(char **ps, int *out)
{
	long	val;
	char	*s;

	s = *ps;
	skip_ws(&s);
	if (!isdigit((unsigned char)*s))
		return (FALSE);
	val = 0;
	while (isdigit((unsigned char)*s))
	{
		val = val * 10 + (*s - '0');
		if (val > 255)
			return (FALSE);
		s++;
	}
	skip_ws(&s);
	*ps = s;
	*out = (int)val;
	return (TRUE);
}

int	read_component(char **ps, int *dst)
{
	if (!parse_int_0_255(ps, dst))
	{
		err("Error\nInvalid color token\n");
		return (FALSE);
	}
	return (TRUE);
}
