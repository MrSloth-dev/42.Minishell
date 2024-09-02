/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:56:35 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/10 13:56:39 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%c, %d,\n", '\n', ft_isprint('\n'));
	printf("%c, %d,\n", '/', ft_isprint('/'));
	printf("%c, %d,\n", ' ', ft_isprint(' '));
	printf("%c, %d,\n", '0', ft_isprint('0'));
	printf("%c, %d,\n", '9', ft_isprint('9'));
	printf("%c, %d,\n", 'A', ft_isprint('A'));
	printf("%c, %d,\n", 'Z', ft_isprint('Z'));
	printf("%c, %d,\n", 'a', ft_isprint('a'));
	printf("%c, %d,\n", 'z', ft_isprint('z'));
	printf("%c, %d,\n", '~', ft_isprint('~'));
	printf("%c, %d,\n", 128, ft_isprint(128));
}*/
