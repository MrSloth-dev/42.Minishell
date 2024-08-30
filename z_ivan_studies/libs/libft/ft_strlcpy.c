/* ************************************************************************** */
/* */
/* ::: ::::::::   */
/*   ft_strlcpy.c    :+: :+:    :+:   */
/*  +:+ +:+    +:+*/
/*   By: isilva-t <marvin@42.fr>+#+  +:+  +#+   */
/*   +#+#+#+#+#+   +#+ */
/*   Created: 2024/04/10 15:31:39 by isilva-t#+#    #+#   */
/*   Updated: 2024/04/10 16:20:49 by isilva-t    ###   ########.fr  */
/* */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (size < 1)
		return (len);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
/*
#include <stdio.h>
int	main(void)
{
	char	dest[10];
	char	src[] = "123456789";
	size_t	size;

	size = 10;
	printf("%lu\n", ft_strlcpy(dest, src, size));
	printf("%s\n", dest);
}*/
