/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:52:13 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 02:52:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*int main ()
{
	char buffer[5];
	int i = 0;
	bzero(buffer,5);


	while (i < 5)
	{
		printf("%d ",buffer[i++]);
	}
	return (0);
}*/
