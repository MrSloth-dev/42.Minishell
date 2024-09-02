/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:46:14 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/19 14:31:32 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	auto int beg = 0, len, i = 0;
	auto char *str;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[beg]) && beg <= len)
		beg++;
	if (beg > len)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[len]))
		len--;
	str = malloc(sizeof(char) * len - beg + 2);
	if (!str)
		return (NULL);
	while (beg <= len)
	{
		str[i] = s1[beg];
		beg++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	const char	s1[] = "12abcdef12";
	const char	set[] = "12";
	char *fr;

	printf("%s, %s\n", s1, set);
	fr = ft_strtrim(s1, set);
	printf("%s\n", fr);
	free (fr);
}*/
