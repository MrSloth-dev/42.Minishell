/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:48:09 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/21 16:48:33 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_syntax_error(int error, t_shell *shell)
{
	char	*name;

	name = "ShellFault: syntax error near";
	if (error == ERR_REDIR_LEFT)
		ft_printf(STDERR_FILENO, "%s unexpected token `<'\n", name);
	else if (error == ERR_REDIR_RIGHT)
		ft_printf(STDERR_FILENO, "%s unexpected token `>'\n", name);
	else if (error == ERR_DBLE_REDIR_LEFT)
		ft_printf(STDERR_FILENO, "%s unexpected token `<<'\n", name);
	else if (error == ERR_DBLE_REDIR_RIGHT)
		ft_printf(STDERR_FILENO, "%s unexpected token `>>'\n", name);
	else if (error == ERR_PIPE_AFTER_REDIR)
		ft_printf(STDERR_FILENO, "%s unexpected token `|'\n", name);
	else if (error == ERR_UNCLOSED_QTE)
		ft_printf(STDERR_FILENO, "%s unclosed quotes\n", name);
	else if (error == ERR_EMPTY_TOKEN)
		ft_printf(STDERR_FILENO, "%s unexpected token `newline'\n", name);
	else if (error == ERR_PIPE)
		ft_printf(STDERR_FILENO, "%s unexpected token `|'\n", name);
	else
		ft_printf(STDERR_FILENO, "%s unexpected token `%c'\n",
			name, (char)error);
	shell->exit_status = 2;
	shell->line = ft_free(shell->line);
}

int	ft_check_status(int status, char c)
{
	if (c == P_DOUBLE_QTE && status == NORMAL)
		status = IN_DOUBLE_QTE;
	else if (c == P_SINGLE_QTE && status == NORMAL)
		status = IN_SINGLE_QTE;
	else if (c == P_DOUBLE_QTE && status == IN_DOUBLE_QTE)
		status = NORMAL;
	else if (c == P_SINGLE_QTE && status == IN_SINGLE_QTE)
		status = NORMAL;
	return (status);
}

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13)
		|| c == ' ')
		return (TRUE);
	else
		return (FALSE);
}

int	ft_is_empty_token(char *line, int direction)
{
	while (*line)
	{
		if (ft_is_space(*line) == TRUE)
		{
			if (direction == RIGHT_TOKEN)
				line++;
			else
				line--;
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

int	ft_have_syntax_error(t_shell *sh)
{
	int		have_error;
	char	*str_error;

	have_error = FALSE;
	str_error = ft_calloc(sizeof(char), (ft_strlen(sh->line) + 2));
	if (!str_error)
		return (ERR_PIPE);
	ft_strlcpy(str_error + 1, sh->line, ft_strlen(sh->line) + 1);
	have_error = ft_have_unclosed_qtes(str_error + 1);
	if (have_error != FALSE)
		return (ft_free(str_error), have_error);
	have_error = ft_check_redirs(str_error + 1);
	if (have_error != FALSE)
		return (ft_free(str_error), have_error);
	have_error = ft_check_pipes(str_error + 1);
	if (have_error != FALSE)
		return (ft_free(str_error), have_error);
	have_error = ft_check_special_char(str_error + 1);
	if (have_error != FALSE)
		return (ft_free(str_error), have_error);
	return (ft_free(str_error), have_error);
}
