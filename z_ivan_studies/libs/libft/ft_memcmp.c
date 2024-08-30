/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:55:37 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/12 13:12:42 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	auto const char *str1, *str2;
	auto size_t i;
	str1 = (const char *)s1;
	str2 = (const char *)s2;
	i = -1;
	while (++i < n)
	{
		if (str1[i] != str2[i])
			return ((int)((unsigned char)str1[i] - (unsigned char)str2[i]));
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[] = "teste_1_31234";
	char	str2[] = "teste_5_31234";
	size_t	n = 7;

	printf("MY %d\n", ft_memcmp(str1, str2, n));
	printf("OR %d\n", memcmp(str1, str2, n));
}*/
