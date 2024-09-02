/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:55 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/11 12:55:53 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	auto size_t i;
	auto unsigned char *ptr;
	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = '\0';
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	str[] = "teste1234";
	size_t	n;
	size_t len = strlen(str);
	size_t	i = 0;

	n = 2;
	printf("%s\n", str);
	ft_bzero(str, n);
	printf("string a seguir 'a quebta linha \n");
	while (i < len)
		write (1, &str[i++], 1);
}*/
