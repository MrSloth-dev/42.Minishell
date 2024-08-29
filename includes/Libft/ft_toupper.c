/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@students.42porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:30:40 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/10 15:34:08 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		return (c - 32);
	return (c);
}
/*
#include <stdio.h>

int main ()
{
	printf("%c", ft_toupper('c'));
	printf("%c", ft_toupper('a'));
	printf("%c", ft_toupper('z'));
	printf("%c", ft_toupper('N'));
	printf("%c", ft_toupper(' '));
	printf("%c", ft_toupper('3'));
	printf("%c", ft_toupper('*'));
	return (0);
}
*/
