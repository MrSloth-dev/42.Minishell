/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:30:56 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/18 09:51:23 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	size_t	nmemb;
	size_t	size;
	char	*ptr;
	
	nmemb = 5;
	size = 2;
	
	printf("before ft_calloc");
	
	ptr = (char *)ft_calloc(nmemb, size);
	printf("\nprint ptr: %c\n(visible 'A', must be ok!)\n", (ptr[0] + 'A'));
	free (ptr);
}*/
