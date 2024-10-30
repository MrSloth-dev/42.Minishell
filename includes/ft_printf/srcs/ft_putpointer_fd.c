/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:39:47 by joao-pol          #+#    #+#             */
/*   Updated: 2024/05/02 15:52:18 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int			ft_printpointer_fd(unsigned long long prt, int fd);
static int	ft_countpointer(unsigned long long prt);

int	ft_putpointer_fd(unsigned long long ptr, int fd)
{
	int		len;

	len = 0;
	if (ptr == 0)
		return (write (1, "(nil)", 5));
	len = write (1, "0x", 2);
	len += ft_printpointer_fd(ptr, fd);
	return (len);
}

int	ft_printpointer_fd(unsigned long long prt, int fd)
{
	if (prt >= 16)
	{
		ft_printpointer_fd(prt / 16, fd);
		ft_printpointer_fd(prt % 16, fd);
	}
	else
		ft_putchar_fd("0123456789abcdef"[prt], fd);
	return (ft_countpointer(prt));
}

static int	ft_countpointer(unsigned long long prt)
{
	int	count;

	count = 0;
	while (prt != 0)
	{
		count++;
		prt = prt / 16;
	}
	return (count);
}
