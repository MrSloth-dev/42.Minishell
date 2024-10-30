/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:26:38 by joao-pol          #+#    #+#             */
/*   Updated: 2024/05/02 16:26:40 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_puthex_fd(unsigned int nbr, char x, int fd)
{
	static int	count;

	count = 0;
	if (nbr / 16 > 0)
	{
		if (x == 'x')
			ft_puthex_fd(nbr / 16, 'x', fd);
		if (x == 'X')
			ft_puthex_fd(nbr / 16, 'X', fd);
	}
	if (x == 'x')
		count += ft_putchar_fd("0123456789abcdef"[nbr % 16], fd);
	if (x == 'X')
		count += ft_putchar_fd("0123456789ABCDEF"[nbr % 16], fd);
	return (count);
}
