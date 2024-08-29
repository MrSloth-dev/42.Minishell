/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:39:02 by joao-pol          #+#    #+#             */
/*   Updated: 2024/05/07 15:47:45 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_concatenate(char *buffer, char *str);
int		ft_check_newline(char *file);
char	*ft_free(char **buffer, char **file);

char	*get_next_line(int fd)
{
	static char	*file = NULL;
	int			i;
	char		*buffer;
	char		*final;

	i = 1;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_check_newline(file) && i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
			return (ft_free(&buffer, &file));
		buffer[i] = '\0';
		file = ft_concatenate(buffer, file);
	}
	final = ft_strdup(file);
	file = ft_cleanfile(file);
	free(buffer);
	return (final);
}

int	ft_check_newline(char *file)
{
	int	i;

	i = 0;
	if (!file)
		return (0);
	while (file[i])
	{
		if (file[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_free(char **buffer, char **file)
{
	free(*buffer);
	free(*file);
	*file = NULL;
	return (NULL);
}

char	*ft_concatenate(char *buffer, char *file)
{
	int			i;
	int			j;
	int			len;
	char		*result;

	if (!buffer)
		return (NULL);
	if (!file)
		file = ft_calloc(1, sizeof(char));
	len = ft_strlen(buffer) + ft_strlen(file);
	result = ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (file[i])
	{
		result[i] = file[i];
		i++;
	}
	while (buffer[j])
		result[i++] = buffer[j++];
	free(file);
	return (result);
}
#include <stdio.h>
