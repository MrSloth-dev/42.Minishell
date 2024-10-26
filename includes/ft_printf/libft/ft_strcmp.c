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

int	ft_strcmp(char *s1, char *s2)
{
	int	diff;
	int	i;

	i = 0;
	diff = 0;
	while (diff == 0 && ((s2[i] || s1[i])))
	{
		diff = s1[i] - s2[i];
		i++;
	}
	return (diff);
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
