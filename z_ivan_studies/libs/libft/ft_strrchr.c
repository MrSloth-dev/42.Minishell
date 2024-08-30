/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:15:04 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/12 12:32:19 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = (int)ft_strlen(str);
	if ((char) c == '\0')
		return ((void *)s + ft_strlen(s));
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (str + i);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	int	c = 't';
	const char	str[] = "teste";
	//const char	str[] = "user_output_test05";

	printf("\nMY: %d\n%s\n\n", c, ft_strrchr(str, c));
	printf("ORIGINAL: %d\n%s\n\n", c, strrchr(str, c));	
}*/
