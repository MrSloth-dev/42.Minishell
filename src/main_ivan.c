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

int	ft_this_pipe_have_error(char *str)
{
	if (!*str || !(str + 1))
		return (ERR_PIPE);
	if (ft_is_empty_token(str - 2, LEFT_TOKEN) == TRUE)
		return (ERR_PIPE);
	while(*str)
	{
		if (ft_is_empty_token(str, RIGHT_TOKEN) == TRUE)
			return (ERR_PIPE);
		str++;
	}
	return (FALSE);
}

int	ft_check_pipes(char *line)
{
	int	pipe_state;
	int	status;

	pipe_state = FALSE;
	status = NORMAL;
	while (*line)
	{
		status = ft_check_status(status, *line);
		if (*line == '|' && status == NORMAL)
		{
			pipe_state = ft_this_pipe_have_error(++line);
			if (pipe_state != FALSE)
				return (pipe_state);
		}
		line++;
	}
	return (pipe_state);
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
	have_error = ft_check_pipes(sh->line);
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
