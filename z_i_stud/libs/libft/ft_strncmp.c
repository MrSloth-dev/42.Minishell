/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:33:02 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/10 17:17:43 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	n = n - 1;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int	main(int argc, char **argv)
{
	if (argc != 3)
		return (0);
	printf("MY : %d\n", ft_strncmp(&argv[1][0], &argv[2][0], 6));
	printf("ORIGINAL : %d\n", strncmp(&argv[1][0], &argv[2][0], 6));	
}

int	main(void)
{
	char s1[] = "test\300";
	char s2[] = "test\0";
	
	//char s1[] = "test1234";
	//char s2[] = "test1345";
	
	size_t	n;
	
	n = 6;
	
	printf("MY : %d\n", ft_strncmp(s1, s2, n));
	printf("ORIGINAL : %d\n", strncmp(s1, s2, n));
}*/
