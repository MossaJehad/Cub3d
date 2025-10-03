/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 03:01:14 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 03:01:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;

	last_occurrence = NULL;
	while (*s != 0)
	{
		if (*s == (char)c)
			last_occurrence = (char *)s;
		s++;
	}
	if (*s == (char)c)
		last_occurrence = (char *)s;
	return (last_occurrence);
}
/*int main()
{
	const char *text = "example string with multiple occurrences of e";
	char *last_occurrence = ft_strrchr(text, 'e');
    	if (last_occurrence)
    	{
		printf("Last occurrence of 'e': %s\n", last_occurrence);
    	}
    	else 
    	{
		printf("'e' not found.\n");
    	}
    	return (0);
}*/
