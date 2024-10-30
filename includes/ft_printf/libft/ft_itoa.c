/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:26 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/18 10:34:45 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_numlen(int nbr);

char	*ft_itoa(int nbr)
{
	auto long nb = nbr;
	auto char *number = NULL;
	auto int i = 0;
	auto int len = ft_numlen(nb);
	auto int neg = (nb < 0);
	if (nb == 0)
		return (ft_strdup("0"));
	number = malloc((len + neg + 1) * sizeof(char));
	if (!number)
		return (NULL);
	else if (nb < 0)
	{
		number[0] = '-';
		nb = -nb;
	}
	while (nb != 0)
	{
		number[len - i - !neg] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	number[len + neg] = 0;
	return (number);
}

static int	ft_numlen(int nbr)
{
	auto int i = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}
