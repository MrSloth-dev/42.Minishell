/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:03:23 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/24 13:14:54 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (*(s + i))
	{
		f(i, s + i);
		i++;
	}
}
/*
void	fun_test(unsigned int i, char *s)
{
	if (i % 2 == 0)
		s[0] = ft_toupper(s[0]);
	else
		s[0] = ft_tolower(s[0]);
}

#include <stdio.h>
int	main(void)
{
	char	s[] = "FRASE para TESTE da FUNCAO";

	printf("Frase Orig: %s\n", s);
	ft_striteri(s, fun_test);
	printf("Frase Resu: %s\n", s);
	return (0);
}*/
