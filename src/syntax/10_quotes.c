/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:47:16 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/21 16:47:22 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_have_unclosed_qtes(char *line)
{
	char	find_this;

	while (*line)
	{
		if (*line == P_SINGLE_QTE || *line == P_DOUBLE_QTE)
		{
			find_this = *line;
			line++;
			while (*line && *line != find_this)
				line++;
			if (!*line || *line != find_this)
				return (ERR_UNCLOSED_QTE);
		}
		if (*line)
			line++;
	}
	return (FALSE);
}
