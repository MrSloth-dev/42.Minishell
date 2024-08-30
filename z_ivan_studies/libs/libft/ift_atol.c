/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:18:07 by isilva-t          #+#    #+#             */
/*   Updated: 2024/06/20 14:22:44 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *nptr)
{
	int	i;
	int	signal;
	int	num;

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
