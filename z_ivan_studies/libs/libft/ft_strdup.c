/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:22:11 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/11 10:46:56 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	auto char *array;
	auto size_t len, i;
	len = ft_strlen(s);
	array = malloc(sizeof(char) * len + 1);
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array[i] = s[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char c[] = "123456789abcdef";
	char	*orig_ft, *my_ft;	
	printf("\n____Original FT____\n");	
	orig_ft = strdup(c);
	printf("%s\n\n", orig_ft);
	
	printf("______My FT_____\n");
	my_ft = ft_strdup(c);
	printf("%s\n", my_ft);
	free(orig_ft);
	free(my_ft);
}*/
