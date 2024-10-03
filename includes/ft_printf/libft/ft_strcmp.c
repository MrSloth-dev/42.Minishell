/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@students.42porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:30:11 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/10 15:34:37 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!s1 || !s2)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (s1[len])
		len++;
	while ((s1[i] && s2[i]) && i < len)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < len)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/* #include <stdio.h>
#include <string.h>
int	main(void)
{
	printf("expected : %d\n", strncmp("test\200", "test\0", 6));
	printf("result : %d\n", ft_strncmp("test\200", "test\0", 6));
	printf("expected : %d\n", strncmp("abcdef", "abc\375xx", 5));
	printf("result : %d\n", ft_strncmp("abcdef", "abc\375xx", 5));
	return (0);
} */
