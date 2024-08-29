/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@students.42porto.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:14:48 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/18 10:52:29 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	if (!dest && !src)
		return (NULL);
	i = 0;
	str1 = (char *) src;
	str2 = (char *) dest;
	while (i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	return (dest);
}
