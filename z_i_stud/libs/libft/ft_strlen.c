/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:04:06 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/10 14:04:08 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include <string.h>
#include <stdio.h>
int	main(int ac, char **av)
{
	(void) ac;
	
	printf("\n____Original FT____\n");
	printf("%lu\n", strlen(av[1]));

	printf("______My FT_____\n");
	printf("%lu\n", ft_strlen(av[1]));
}*/
