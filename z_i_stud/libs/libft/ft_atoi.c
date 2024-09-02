/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:31:24 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/11 17:48:51 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	auto int i, signal, num;
	i = 0;
	signal = 1;
	num = 0;
	while ((nptr[i] != '\0' && nptr[i] >= '\t' && nptr[i] <= '\r')
		|| nptr[i] == ' ')
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i++] == '-')
			signal = -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i] != '\0')
	{
		num = num * 10 + nptr[i++] - '0';
	}
	return (num * signal);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf(" number of arguments incorrect");
		return (0);
	}
	printf("%d", ft_atoi(&av[1][0]));
}*/

/*int	main(void)
{
	char t[] =  " \t\v\n\r\f123";
	
	printf("MY:	%d\n", ft_atoi(t));
	printf("ORIGINAL: %d\n", atoi(t));
}
*/
