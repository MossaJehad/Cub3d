/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:52:34 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 02:52:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		value;

	p = s;
	value = (unsigned char)c;
	while (n--)
	{
		if (*p == value)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
/*int main() {
    char buffer[] = "Hello, World!";
    char *result;

    result = ft_memchr(buffer, 'W', sizeof(buffer));

    if (result) {
        printf("Character found: %c\n", *result);
    } else {
        printf("Character not found.\n");
    }

    return 0;
}*/
