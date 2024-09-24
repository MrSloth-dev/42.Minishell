/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:47:44 by joao-pol          #+#    #+#             */
/*   Updated: 2024/09/07 01:48:05 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

void ft_print_syntax_error(int	error)
{
	char name[] = "ShellFault: syntax error near";
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
}

///////////////////////////////////////////////////////////
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

int	ft_is_empty_token(char *line)
{
	while (*line)
	{
		if (ft_is_space(*line) == TRUE)
			line++;
		else
			return (FALSE);
	}
	return (TRUE);
}
///////////////////////

int	ft_check_this_redir_text(char *str, char tmp)
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

int	ft_what_have_after_redir(char *str)
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

int	ft_this_redir_have_error(char *str)
{
	int		after_redir_err;
	char	redir;

	after_redir_err = FALSE;
	redir = *str;
	str++;
	if (*str && *str == redir)
		str++;
	if (ft_is_empty_token(str) == TRUE)
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







int	ft_have_syntax_error(t_shell *sh)
{
	int	have_error;

	have_error = FALSE;
	have_error = ft_have_unclosed_qtes(sh->line);
	if (have_error != FALSE)
		return (have_error);
	have_error = ft_check_redirs(sh->line);
	if (have_error != FALSE)
		return (have_error);
	return (have_error);
}

int	main(void)
{
	t_shell	sh;
	int	have_syn_error;

	while (1)
	{
		ft_readline(&sh);
		have_syn_error = ft_have_syntax_error(&sh);
		if (have_syn_error != FALSE)
			ft_print_syntax_error(have_syn_error);
	}
	return (0);
}

/* int main()
{
	t_shell sh;
	char *str= "echo hello my love";
	char **split = ft_split(str, ' ');
	ft_echo(split, &sh);
} */

/* char	*get_next_line(int fd);

int	main(void)
{
	char	*line;
	int		fd;

	fd = 0;
	write(2, "\033[2J\033[H", 8);
	write(STDOUT_FILENO, "Please write your command >>  ", 30);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp("exit", line, 4) == 0)
			return (free(line), 0);
		if (ft_strncmp("hello", line, 5) == 0)
			write(0, "teste\n", 5);
		write(STDOUT_FILENO, "Please write your command >>  ", 30);
		line = get_next_line(fd);
	}
	return (0);
} */
