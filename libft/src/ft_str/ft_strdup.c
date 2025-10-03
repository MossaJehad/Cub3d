/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:02:02 by marvin            #+#    #+#             */
/*   Updated: 2025/09/04 20:02:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*dest;
	size_t		length;

	length = ft_strlen(s);
	dest = malloc(length + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, length + 1);
	return (dest);
}
