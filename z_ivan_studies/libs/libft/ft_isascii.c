/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:50:51 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/10 12:51:53 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%c, %d,\n", '\n', ft_isascii('\n'));
	printf("%c, %d,\n", '/', ft_isascii('/'));
	printf("%c, %d,\n", '0', ft_isascii('0'));
	printf("%c, %d,\n", '9', ft_isascii('9'));
	printf("%c, %d,\n", 'A', ft_isascii('A'));
	printf("%c, %d,\n", 'Z', ft_isascii('Z'));
	printf("%c, %d,\n", 'a', ft_isascii('a'));
	printf("%c, %d,\n", 'z', ft_isascii('z'));
	printf("%c, %d,\n", 128, ft_isascii(128));
}*/
