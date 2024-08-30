/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:09:29 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/09 16:21:39 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%c, %d,\n", '\n', ft_isalpha('\n'));
	printf("%c, %d,\n", '/', ft_isalpha('/'));
	printf("%c, %d,\n", '0', ft_isalpha('0'));
	printf("%c, %d,\n", '9', ft_isalpha('9'));
	printf("%c, %d,\n", 'A', ft_isalpha('A'));
	printf("%c, %d,\n", 'Z', ft_isalpha('Z'));
	printf("%c, %d,\n", 'a', ft_isalpha('a'));
	printf("%c, %d,\n", 'z', ft_isalpha('z'));
	printf("%c, %d,\n", 128, ft_isalpha(128));
}*/
