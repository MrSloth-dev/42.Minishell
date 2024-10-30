/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:48:50 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/21 16:48:53 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_this_redir_text(char *str, char tmp)
{
	if (*str && *str == tmp)
	{
		if (*str == '<')
			return (ERR_DBLE_REDIR_LEFT);
		else
			return (ERR_DBLE_REDIR_RIGHT);
	}
	else if (tmp == '<')
		return (ERR_REDIR_LEFT);
	else
		return (ERR_REDIR_RIGHT);
}

static int	ft_what_have_after_redir(char *str)
{
	char	tmp;

	while (*str)
	{
		tmp = *str;
		if (*str == '<' || *str == '>')
			return (ft_check_this_redir_text(++str, tmp));
		else if (*str == '|')
			return (ERR_PIPE_AFTER_REDIR);
		if (ft_is_space(*str) == FALSE)
			return (FALSE);
		str++;
	}
	return (FALSE);
}

static int	ft_this_redir_have_error(char *str)
{
	int		after_redir_err;
	char	redir;

	after_redir_err = FALSE;
	redir = *str;
	str++;
	if (*str && *str == redir)
		str++;
	if (ft_is_empty_token(str, RIGHT_TOKEN) == TRUE)
		return (ERR_EMPTY_TOKEN);
	if (*str)
		after_redir_err = ft_what_have_after_redir(str);
	return (after_redir_err);
}

int	ft_check_redirs(char *line)
{
	int	status;
	int	redir_state;

	redir_state = FALSE;
	status = NORMAL;
	while (*line)
	{
		status = ft_check_status(status, *line);
		if ((*line == '<' || *line == '>')
			&& (status == NORMAL))
		{
			redir_state = ft_this_redir_have_error(line);
			if (redir_state != FALSE)
				return (redir_state);
		}
		line++;
	}
	return (redir_state);
}
