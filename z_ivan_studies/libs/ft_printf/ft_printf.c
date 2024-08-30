/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:54:47 by isilva-t          #+#    #+#             */
/*   Updated: 2024/05/08 09:54:51 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putchar(int c);
int	pf_print_str(char *str, int cont);

int	pf_print_format(char spec, va_list *ap, int cont)
{
	if (spec == 'c')
		cont += pf_putchar(va_arg(*ap, int));
	else if (spec == 'p')
		cont += pf_print_ptr(va_arg(*ap, unsigned long long), 0);
	else if (spec == 'd' || spec == 'i')
		cont += pf_put_nbr_base((long)va_arg(*ap, int), 10, 0);
	else if (spec == 's')
		cont += pf_print_str(va_arg(*ap, char *), 0);
	else if (spec == 'u')
		cont += pf_put_nbr_base(va_arg(*ap, unsigned int), 10, 0);
	else if (spec == 'X')
		cont += pf_put_nbr_base(va_arg(*ap, unsigned int), 16, -32);
	else if (spec == 'x')
		cont += pf_put_nbr_base(va_arg(*ap, unsigned int), 16, 0);
	else if (spec == '%')
		cont += pf_putchar('%');
	else
		return (0);
	return (cont);
}

int	pf_verify(char c, int i)
{
	char	*cache;

	cache = "cspdiuxX%";
	while (cache[i])
	{
		if (cache[i++] == c)
			return (1);
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		cont;
	int		i;

	va_start(ap, s);
	cont = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%' && s[i + 1] && pf_verify(s[i + 1], 0) == 1)
			cont += pf_print_format(s[++i], &ap, 0);
		else
			cont += pf_putchar(s[i]);
		i++;
	}
	va_end(ap);
	return (cont);
}

int	pf_print_str(char *str, int cont)
{
	if (!str)
		str = "(null)";
	while (str[cont])
	{
		pf_putchar(str[cont++]);
	}
	return (cont);
}

int	pf_putchar(int c)
{
	return (write(1, &c, 1));
}
