/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:02:30 by joao-pol          #+#    #+#             */
/*   Updated: 2024/05/07 14:40:29 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(char *s, size_t n)
{
	s[n - 1] = '\0';
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb * size == 0)
		return ((void *) malloc(0));
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*result;

	if (!str || !*str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	result = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = str[i];
	return (result);
}

char	*ft_cleanfile(char *file)
{
	char	*result;
	int		i;
	int		j;
	int		length;

	if (!*file)
	{
		free(file);
		return (NULL);
	}
	length = ft_strlen(file);
	i = 0;
	while (file[i] != '\0' && file[i] != '\n')
		i++;
	result = ft_calloc(((length - i) + 1), sizeof(char));
	j = 0;
	while (file[i])
	{
		result[j++] = file[++i];
	}
	result[j] = '\0';
	free(file);
	return (result);
}
