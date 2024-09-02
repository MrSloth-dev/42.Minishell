/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <username@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:01:14 by username          #+#    #+#             */
/*   Updated: 2024/05/14 14:50:00 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char	*get_next_line(int fd);
char	*gnl_ft_strchr(char *s, int c);
size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_substr(char const *line, unsigned int start, size_t len);
char	*gnl_ft_strdup(const char *src);
char	*gnl_ft_strjoin(const char *line, char const *buf);

#endif
