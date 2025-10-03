/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:44:21 by marvin            #+#    #+#             */
/*   Updated: 2025/09/07 23:38:34 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	err(const char *msg)
{
	return ((int)write(2, msg, ft_strlen(msg)));
}

int	is_space_line(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '\0');
}

char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

char	*sdup(const char *s)
{
	size_t	n;
	char	*r;

	n = ft_strlen(s);
	r = (char *)malloc(n + 1);
	if (!r)
		return (NULL);
	ft_memcpy(r, s, n);
	r[n] = '\0';
	return (r);
}

void	free_cfg(t_cfg *c)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(c->tex[i]);
		i++;
	}
	i = 0;
	while (i < c->lines.size)
		free(c->lines.data[i++]);
	free(c->lines.data);
	i = 0;
	if (c->map)
	{
		while (i < c->map_h)
			free(c->map[i++]);
		free(c->map);
	}
}
