/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:29:01 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/24 10:56:34 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(str + i) = f(i, *(s + i));
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
/*
char	fun_test(unsigned int i, char c)
{
	if (i % 2 == 0)
		c = ft_toupper(c);
	else if (i % 2 == 1)
		c = ft_tolower(c);
	return (c);
}

#include <stdio.h>
int	main(void)
{
	char	*s = "FRASE para TESTE da FUNCAO";
	char	*str_result;

	str_result = ft_strmapi(s, fun_test);
	printf("Frase Orig: %s\nFrase Resu: %s\n", s, str_result);
	free (str_result);
	return (0);
}*/
