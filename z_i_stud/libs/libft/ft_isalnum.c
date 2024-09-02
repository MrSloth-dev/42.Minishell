/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:09:29 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/16 11:28:45 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) == 1 || (ft_isalpha(c) == 1))
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%c, %d,\n", '\n', ft_isalnum('\n'));
	printf("%c, %d,\n", '/', ft_isalnum('/'));
	printf("%c, %d,\n", '0', ft_isalnum('0'));
	printf("%c, %d,\n", '9', ft_isalnum('9'));
	printf("%c, %d,\n", 'A', ft_isalnum('A'));
	printf("%c, %d,\n", 'Z', ft_isalnum('Z'));
	printf("%c, %d,\n", 'a', ft_isalnum('a'));
	printf("%c, %d,\n", 'z', ft_isalnum('z'));
}*/
