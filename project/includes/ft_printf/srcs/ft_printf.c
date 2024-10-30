/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:56:04 by joao-pol          #+#    #+#             */
/*   Updated: 2024/05/03 13:07:33 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_formatprint(char format, va_list ap, int fd);

int	ft_printf(int fd, const char *str, ...)
{
	va_list	ap;
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			count += ft_formatprint(str[i], ap, fd);
		}
		else
			count += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(ap);
	return (count);
}

int	ft_formatprint(char format, va_list ap, int fd)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_putchar_fd(va_arg(ap, int), fd);
	else if (format == 'd')
		count += ft_putnbr_fd(va_arg(ap, int), fd);
	else if (format == 's')
		count += ft_putstr_fd(va_arg(ap, char *), fd);
	else if (format == 'i')
		count += ft_putnbr_fd(va_arg(ap, int), fd);
	else if (format == 'p')
		count += ft_putpointer_fd(va_arg(ap, unsigned long long), fd);
	else if (format == 'u')
		count += ft_uputnbr_fd(va_arg(ap, int), fd);
	else if (format == 'x')
		count += ft_puthex_fd(va_arg(ap, int), 'x', fd);
	else if (format == 'X')
		count += ft_puthex_fd(va_arg(ap, int), 'X', fd);
	else if (format == '%')
		count += ft_putchar_fd('%', fd);
	return (count);
}
