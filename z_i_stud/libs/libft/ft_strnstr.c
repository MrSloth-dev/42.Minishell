/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:37:17 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/12 18:10:01 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		if (big[i] == little[0])
		{
			while ((big[i + j] == little[j]) && ((i + j) < len)
				&& (big[i + j] != '\0'))
			{
				j++;
				if (little[j] == '\0')
					return ((char *)big + i);
			}
		}
		i++;
	}
	return (NULL);
}
/*
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	const char	big[] = "frase_de_teste";
	const char	little[] = "ase";
	size_t	len = 5;

	printf("Big: %s, Len: %lu\n\n", big, len);
	
	printf("MY %s\n", ft_strnstr(big, little, len));
	
	printf("OR %s\n", strnstr(big, little, len));
}
*/
