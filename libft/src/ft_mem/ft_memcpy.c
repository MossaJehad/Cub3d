/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:52:53 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 02:52:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	const char		*buffer1;
	char			*buffer2;

	i = 0;
	buffer1 = (char *)src;
	buffer2 = dest;
	while (i < n && (src || dest))
	{
		buffer2[i] = buffer1[i];
		i++;
	}
	return (dest);
}
/*int main()
{
    char buffer[10];
    char dest[10]; 
    int i = 0;

    ft_memset(buffer, 'a', sizeof(buffer));
    ft_memcpy(dest, buffer, sizeof(buffer));


    while (i < sizeof(dest))
    {
        printf("%c ", dest[i]); 
        i++;
    }
    printf("\n");

    return 0;
}*/
