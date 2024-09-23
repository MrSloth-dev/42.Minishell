/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@students.42porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:30:27 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/10 15:34:00 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		return (c + 32);
	return (c);
}
/*
#include <stdio.h>

int main ()
{
	printf("%c", ft_tolower('c'));
	printf("%c", ft_tolower('a'));
	printf("%c", ft_tolower('z'));
	printf("%c", ft_tolower('N'));
	printf("%c", ft_tolower(' '));
	printf("%c", ft_tolower('3'));
	printf("%c", ft_tolower('*'));
	return (0);
}
*/
