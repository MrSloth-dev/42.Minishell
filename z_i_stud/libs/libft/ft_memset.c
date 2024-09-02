/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:48:08 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/11 12:26:10 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i++] = (unsigned char)c;
	}
	return (s);
}
/*
#include <stdio.h>
int	main(void)
{
	unsigned char str[] = "teste";
	int	c;
	size_t	n;

	c = 'a';
	n = 2;
//	ft_memset(str, c, n);
//	printf("%s", str);
	printf("%s", (char *)(ft_memset(str, c, n)));
	return (0);
}*/
