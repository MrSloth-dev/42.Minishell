/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:54:40 by isilva-t          #+#    #+#             */
/*   Updated: 2024/05/08 09:54:43 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_ptr(unsigned long long n, int cont)
{
	char	*n_cache;

	cont = 0;
	n_cache = "0123456789abcdef";
	if (n >= 16)
	{
		cont += (put_ptr(n / 16, cont));
		return (cont + put_ptr(n % 16, cont));
	}
	else
		return (cont + pf_putchar(n_cache[n]));
}

int	pf_print_ptr(unsigned long long ptr, int cont)
{
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	else
	{
		cont += write(1, "0x", 2);
		cont += put_ptr(ptr, cont);
	}
	return (cont);
}
