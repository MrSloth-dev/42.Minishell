/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:41:14 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/18 13:28:43 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*substr;
	size_t	i;

	substr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) +1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		substr[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		substr[i] = *s2;
		i++;
		s2++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
#include <stdio.h>
int     main(void)
{
	const char s1[] = "teste";
	const char s2[] = "12345";
	char	*str;
	printf("%s\n%s\n", s1, s2);
	str = ft_strjoin(s1, s2);
	printf("%s\n", str);
	free(str);
}*/
