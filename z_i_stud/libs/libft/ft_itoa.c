/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:10:48 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/23 11:48:32 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(long n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (len + 1);
	if (n < 0)
	{
		len++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*space_str(int len)
{
	char	*str;

	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	return (str);
}

static long	abs_value(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	auto int len, space_minus = 0, i = 0;
	auto long nbr_long;
	auto char *str;
	if (n < 0)
		space_minus = 1;
	len = get_len(n);
	nbr_long = abs_value((long)n);
	str = space_str(len);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[len - i++ - 1] = nbr_long % 10 + '0';
		if (len - i - 1 == 0 && space_minus == 1)
		{
			str[len - i++ - 1] = '-';
			continue ;
		}
		nbr_long = nbr_long / 10;
	}
	str[len] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	//int	n = -2147483648;
	//int	n = 2147483647;
	//int	n = -21;
	int	n = 0;
	char	*str;
	
	str = ft_itoa(n);
	if (!str)
		return (0);
	printf("str: %s\n", str);
	free (str);
	return (0);
}*/
