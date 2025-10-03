/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:03:16 by marvin            #+#    #+#             */
/*   Updated: 2025/09/07 23:44:51 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*join_free(char *s, const char *buf, ssize_t n)
{
	size_t	ls;
	char	*r;

	ls = ft_strlen(s);
	r = (char *)malloc(ls + n + 1);
	if (!r)
		return (free(s), NULL);
	ft_memcpy(r, s, ls);
	ft_memcpy(r + ls, buf, n);
	r[ls + n] = '\0';
	free(s);
	return (r);
}

static int	handle_read_error(char **ps)
{
	if (*ps)
	{
		free(*ps);
		*ps = NULL;
	}
	err("Error\nRead failed\n");
	return (-1);
}

static int	append_buffer(char **ps, char *buf, ssize_t n)
{
	char	*ns;

	ns = join_free(*ps, buf, n);
	if (!ns)
	{
		err("Error\nOOM\n");
		*ps = NULL;
		return (0);
	}
	*ps = ns;
	return (1);
}

static int	read_into_string(int fd, char **ps)
{
	ssize_t	n;
	char	buf[4096];
	int		rc;

	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, sizeof(buf));
		if (n < 0)
			return (handle_read_error(ps));
		if (n > 0)
		{
			rc = append_buffer(ps, buf, n);
			if (rc != 1)
				return (rc);
		}
	}
	return (1);
}

char	*file_to_str(const char *path)
{
	int		fd;
	char	*s;
	int		rc;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		err("Error\nCannot open file\n");
		return (NULL);
	}
	s = sdup("");
	if (!s)
	{
		close(fd);
		err("Error\nOOM\n");
		return (NULL);
	}
	rc = read_into_string(fd, &s);
	close(fd);
	if (rc == 1)
		return (s);
	return (NULL);
}
