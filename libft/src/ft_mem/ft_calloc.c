/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:52:22 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 02:52:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			total;
	size_t			i;

	total = nmemb * size;
	ptr = malloc(total);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (i < total)
		ptr[i++] = 0;
	return (ptr);
}
