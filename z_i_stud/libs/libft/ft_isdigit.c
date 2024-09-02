/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:09:29 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/09 16:25:43 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%c, %d,\n", '\n', ft_isdigit('\n'));
	printf("%c, %d,\n", '/', ft_isdigit('/'));
	printf("%c, %d,\n", '0', ft_isdigit('0'));
	printf("%c, %d,\n", '5', ft_isdigit('5'));
	printf("%c, %d,\n", '9', ft_isdigit('9'));
	printf("%c, %d,\n", 'A', ft_isdigit('A'));
	printf("%c, %d,\n", 'Z', ft_isdigit('Z'));
	printf("%c, %d,\n", 'a', ft_isdigit('a'));
	printf("%c, %d,\n", 'z', ft_isdigit('z'));
	printf("%c, %d,\n", 128, ft_isdigit(128));
}*/
