/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:58:23 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 02:58:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_length;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_length = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(total_length + 1);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	ft_strlcpy(result, s1, total_length + 1);
	ft_strlcat(result, s2, total_length + 1);
	return (result);
}
