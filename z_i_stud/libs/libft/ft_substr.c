/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:35:47 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/18 11:26:14 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	auto char *array;
	auto unsigned int i;
	auto unsigned int str_len;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (str_len < start)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	array = malloc(sizeof(char) * len + 1);
	if (array == NULL)
		return (NULL);
	i = 0;
	while (len--)
	{
		array[i++] = s[start++];
	}
	array[i] = '\0';
	return (array);
}
/*
#include <stdio.h>
int     main(void)
{
    const char s[] = "abcdefgh";
	char	*str;
    unsigned int    start = 2;
    size_t  len = 5;        

    printf("____________ft_substr___________\n");
	str = ft_substr(s, start, len);
	printf("	%s\nend ft!\n", str);
	free (str);
}*/
