/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:43:54 by isilva-t          #+#    #+#             */
/*   Updated: 2024/05/17 11:10:58 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_search_new_line(int fd, char *buf, char *backup_static)
{
	int		read_check;
	char	*temp_to_free;

	read_check = 1;
	while (read_check)
	{
		read_check = read(fd, buf, BUFFER_SIZE);
		if (read_check == -1)
			return (NULL);
		else if (read_check == 0)
			break ;
		buf[read_check] = '\0';
		if (!backup_static)
			backup_static = gnl_ft_strdup("");
		temp_to_free = backup_static;
		backup_static = gnl_ft_strjoin(temp_to_free, buf);
		if (!backup_static)
			return (NULL);
		free (temp_to_free);
		temp_to_free = NULL;
		if (gnl_ft_strchr(buf, '\n'))
			break ;
	}
	return (backup_static);
}

static char	*ft_rest_to_next_call(char *line)
{
	int		i;
	char	*rest;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\0')
		return (NULL);
	rest = gnl_ft_substr(line, i + 1, gnl_ft_strlen(line) - i);
	if (!rest)
		return (NULL);
	if (rest[0] == '\0')
	{
		free (rest);
		rest = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*backup_static;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = ft_search_new_line(fd, buf, backup_static);
	free (buf);
	if (!line)
		return (NULL);
	backup_static = ft_rest_to_next_call(line);
	return (line);
}
