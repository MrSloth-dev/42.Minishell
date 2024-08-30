/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:43:38 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/11 15:51:14 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	auto size_t i_src, i_dst, result;
	i_src = ft_strlen(src);
	i_dst = ft_strlen(dst);
	result = i_src;
	if (size <= i_dst)
		result += size;
	else
		result += i_dst;
	i_src = 0;
	while (src[i_src] != '\0' && i_dst + 1 < size)
		dst[i_dst++] = src[i_src++];
	dst[i_dst] = '\0';
	return (result);
}
/*
#include <stdio.h>

int	main(void)
{
	const char src[] = "12345";
	char dst[] = "destino_com_";
	size_t size;
	
	size = 20;

	printf("variavel src 	    : %s\nvariavel dst inicial: %s\n", src, dst);
	
	printf("\nreturn da ft_strlcat: %zu\n\n", ft_strlcat(dst, src, size));
	printf("variavel dst depois ft: %s\n\n", dst);
}*/
