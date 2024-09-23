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

int	ft_have_unclosed_qtes(char *line)
{
	int	have_uncl_qte;
	char	find_this;

	have_uncl_qte = FALSE;
	while (*line)
	{
		if (*line == P_SINGLE_QTE || *line == P_DOUBLE_QTE)
		{
			find_this = *line++;
			while (*line && *line != find_this)
				line++;
			if (!*line || *line != find_this)
				have_uncl_qte = ERR_UNCLOSED_QTE;
		}
		if (*line)
		line++;
	}
	return (have_uncl_qte);
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

int	ft_have_pipes_or_redirs_next(char *str)
{
	char	*check;

	check = 0;
	while (*str)
	{
		check = 0;
		check = ft_strchr("<>", *str);
		if (*check != 0)
		{
			if (*str + 1 && (*str + 1) == *check)
			{
				if (*check == '<')
					return (ERR_DBLE_REDIR_LEFT);
				else
					return (ERR_DBLE_REDIR_RIGHT);
			}
		}
		if (*str == '|')
			return (ERR_PIPE);
		if (ft_is_space(*str) == FALSE)
			return (FALSE);
		else
			str++;
	}
	return (FALSE);
}

int	ft_this_redir_have_error(char *str)
{
	int		redir_type;
	char	redir;

	redir_type = SINGLE;
	redir = *(str++);
	if (*str && *str == redir)
	{
		str++;
		redir_type = DOUBLE;
	}
	if (ft_is_empty_token(str) == TRUE)
	{
		ft_printf(STDERR_FILENO, "minishell: syntax error near unexpected token `newline'\n");
		return (TRUE);
	}
	if (ft_have_pipes_or_redirs_next(str, redir) != FALSE)
	{
		if (redir_type == DOUBLE)
			ft_printf(STDERR_FILENO, "minishell: syntax error near unexpected token `%c%c'\n", redir, redir);
		else
			ft_printf(STDERR_FILENO, "minishell: syntax error near unexpected token `%c'\n", redir);
		return (TRUE);
	}
	return (FALSE);
}

int	ft_have_redir_error(char *line)
{
	int	status;

	status = NORMAL;
	while (*line)
	{
		status = ft_check_status(status, *line);
		if ((*line == P_REDIR_LEFT || *line == P_REDIR_RIGHT)
			&& (status == NORMAL))
		{
			if (ft_this_redir_have_error(line) == TRUE)
				return (TRUE);
		}
		line++;
	}
	return (FALSE);
}

int	ft_have_syntax_error(t_shell *sh)
{
	int	have_error;

	have_error = ft_have_unclosed_qtes(sh->line);
	if (have_error != FALSE)
		return (have_error);
	have_error = ft_have_redir_error(sh->line);
	if (have_error != FALSE)
		return (have_error);
	return (have_error);
}

int	main(void)
{
	t_shell	sh;
	int	have_syn_err;

	while (1)
	{
		ft_readline(&sh);
		have_syn_err = ft_have_syntax_error(&sh);
		if (have_syn_err == TRUE)
			printf("Syntax error! need free??\n");
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
