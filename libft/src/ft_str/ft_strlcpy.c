/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:58:38 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 02:58:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;
	size_t		length;

	s = src;
	length = 0;
	while (*s++)
		length++;
	if (size == 0)
		return (length);
	while (*src != 0 && --size)
		*dst++ = *src++;
	*dst = 0;
	return (length);
}
