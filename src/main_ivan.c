/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ivan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:47:44 by joao-pol          #+#    #+#             */
/*   Updated: 2024/09/24 17:09:47 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	have_error = ft_check_special_char(sh->line);
	if (have_error != FALSE)
		return (have_error);
	return (have_error);
}


int	ft_is_word(char c)
{
	if (c && (c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '$'
		|| c == '"'
		|| c == '\''
		|| ft_is_space(c) == TRUE))
			return (FALSE);
	return (TRUE);
}

int	ft_how_much_consequent_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_is_space(str[i]) == TRUE)
		i++;
	printf("consequent %d spaces\n", i);
	return (i);
}

void	ft_tokenizer(char *line)
{
	int	status;
	int	i;

	status = NORMAL;
	i = -1;
	while (line[++i])
	{
		status = ft_check_status(status, line[i]);
		if (ft_is_word(line[i]) == TRUE && status == NORMAL)
			printf("append_word\n");
		else if (ft_is_space(line[i]) == TRUE)
			i += ft_how_much_consequent_spaces(line + i) - 1;
		else if (line[i] == '|')
			printf("\nhere is a PIPE\n\n");
		else if (line[i] == '$')
			printf("Oh my god, here is a DOLLAR! lets check heredoc!\n");
		else if (line[i] == '<' || line[i] == '>')
			printf("\nthere is a redir\n\n");
		else if (status == NORMAL && (line[i] == '"' || line[i] == '\''))
			printf(" FUCKING QUOTES TO APPEND!\n");
	}
}





void	ft_shellfault(t_shell *sh)
{
	ft_tokenizer(sh->line);
}

void	test_bzero(void *s, size_t n)
{
	auto size_t i;
	auto unsigned char *ptr;
	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = '\0';
}
void	*test_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb * size == 0)
		return ((void *) malloc(0));
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	test_bzero(ptr, nmemb * size);
	return (ptr);
}

t_shell	*ft_init_shell()
{
	t_shell	*sh;
	sh = test_calloc(1, sizeof(t_shell));
	if (!sh)
	{
		printf("Error on calloc \"sh\" struct!\n");
		return (NULL);
	}
	
	return (sh);
}



int	main(void)
{
	t_shell	*sh;
	int	have_syn_error;

	sh = ft_init_shell();
	while (1)
	{
		ft_readline(sh);
		have_syn_error = ft_have_syntax_error(sh);
		if (have_syn_error != FALSE)
			ft_print_syntax_error(have_syn_error);
		else
			ft_shellfault(sh);

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
