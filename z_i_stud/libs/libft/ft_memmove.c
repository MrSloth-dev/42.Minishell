/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:29:46 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/18 08:45:30 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		while (n)
		{
			n--;
			((char *)dest)[n] = ((char *)src)[n];
		}
	}
	return (dest);
}

/*
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
	ft_memmove(dest, src, n);
	
// original function
	//memmove(dest, src, n);
	
	printf("final dest:	%s\n", dest);
}
*/
