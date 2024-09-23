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
				have_uncl_qte = TRUE;
		}
		if (*line)
		line++;
	}
	if (have_uncl_qte == TRUE)
		printf("Error: have unclosed quotes!\n");
	return (have_uncl_qte);
}

enum en_status	ft_check_status(enum en_status status, char c)
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

int	ft_have_redir_error(char *line)
{
	enum en_status	status;

	status = NORMAL;
	while (*line)
	{
		status = ft_check_status(status, *line);
		if ((*line == P_REDIR_LEFT || *line == P_REDIR_RIGHT)
			&& (status == NORMAL))
		{
			printf("lets check redir here!\n");
		}
	}
	return (FALSE);
}

int	ft_have_syntax_error(t_shell *sh)
{
	if (ft_have_unclosed_qtes(sh->line) == TRUE)
		return (TRUE);
	if (ft_have_redir_error(sh->line) == TRUE)
		return (TRUE);
	return (FALSE);
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
			printf("Syntax error!\n");
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
