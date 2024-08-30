/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:19:27 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/11 13:35:08 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	src[] = "teste1234";
	char	dest[] = "123456789";
	size_t	n;

	n = 3;

	printf("src:		%s\n", src);
	printf("dest: 		%s\n", dest);
	printf("n:		%zd\n\n", n);
	// my function
	ft_memcpy(dest, src, n);
	// original function
	//memcpy(dest, src, n);
	printf("final dest:	%s\n", dest);
}*/
