/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:36:20 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/12 12:54:12 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*res;

	res = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (n != 0)
	{
		if (*res == (unsigned char)c)
			return (res);
		++res;
		--n;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "teste131234";
	int	c = '1';
	//char	*my_fun;
	size_t	n = 15;

	//my_fun = (char *)ft_memchr(str, c, n);
	printf("MY %s\n", (char *)ft_memchr(str, c, n));
	printf("OR %s\n", (char *)memchr(str, c, n));
}*/
