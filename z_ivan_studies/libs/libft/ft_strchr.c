/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:25:15 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/16 13:17:04 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	if ((char)c == '\0')
		return ((void *)str + ft_strlen(s));
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	int	c = 'e';
	const char	str[] = "teste";

	printf("MY: %d\n%s\n\n", c, ft_strchr(str, c));
	printf("ORIGINAL: %d\n%s\n\n", c, strchr(str, c));
}
*/
