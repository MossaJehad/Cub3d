/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:12:02 by marvin            #+#    #+#             */
/*   Updated: 2025/09/12 03:34:26 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	skip_ws(char **ps)
{
	while (**ps == ' ' || **ps == '\t')
		(*ps)++;
}

int	rtrim_len(const char *s)
{
	int	len;

	len = (int)ft_strlen(s);
	while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\t'
			|| s[len - 1] == '\r'))
		len--;
	return (len);
}

int	expect_comma(char **ps)
{
	if (**ps != ',')
	{
		err("Error\nColor needs 3 values\n");
		return (FALSE);
	}
	(*ps)++;
	return (TRUE);
}

int	try_open_texture(const char *p)
{
	int	fd;

	fd = open(p, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}

char	*dup_trimmed_path(char *s)
{
	int		len;
	char	*path;

	skip_ws(&s);
	len = rtrim_len(s);
	path = (char *)malloc((size_t)len + 1);
	if (!path)
	{
		err("Error\nOOM\n");
		return (NULL);
	}
	ft_memcpy(path, s, (size_t)len);
	path[len] = '\0';
	return (path);
}
