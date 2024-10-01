/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ivan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:47:44 by joao-pol          #+#    #+#             */
/*   Updated: 2024/09/25 16:27:43 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
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
	if (!c)
		return (FALSE);
	if (c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '$'
		|| c == '"'
		|| c == '\''
		|| ft_is_space(c) == TRUE)
		return (FALSE);
	else
		return (TRUE);
}

int	ft_how_much_consequent_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_space(str[i]) == TRUE)
		i++;
	return (i);
}

void	ft_append_node(t_token_lst *token_lst, char *str, int type)
{
	t_token	*cur;
	t_token	*new_token;

	cur = NULL;
	new_token = ft_calloc(sizeof(t_token), 1);
	if (!new_token)
		return ;

	new_token->content = str;
	new_token->type = type;
	new_token->next = NULL;

	if (!token_lst->first)
	{
		token_lst->first = new_token;
		new_token->prev = NULL;
	}
	if (token_lst->first)
	{
		cur = token_lst->first;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
		new_token->prev = cur;
	}
}

int	ft_append_word(t_token_lst *token_lst, char *str, int type)
{
	int	j;

	j = 0;
	if (type == WORD)
	{
		while (str[j] && ft_is_word(str[j]) == TRUE)
			j++;
		ft_append_node(token_lst, ft_substr(str, 0, j), type);
	}
	return(j);
}



void	ft_tokenizer(t_token_lst *token_lst, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_is_word(line[i]) == TRUE)
		{
			i += ft_append_word(token_lst, line + i, WORD) - 1;
			if (!line[i])
				break;
		}
		else if (ft_is_space(line[i]) == TRUE)
		{
			ft_append_node(token_lst, ft_strdup("_"), WHITE_SPACE);
			i += ft_how_much_consequent_spaces(line + i) - 1;
		}
		else
		{
			i++;
		}
		// else if (line[i] == '|')
		// {
		// 	printf("\nhere is a PIPE\n\n");
		// }
		// else if (line[i] == '$')
		// {
		// 	printf("Oh my god, here is a DOLLAR! lets check heredoc!\n");
		// }
		// else if (line[i] == '<' || line[i] == '>')
		// {
		// 	printf("\nthere is a redir\n\n");
		// }
		// else if ((line[i] == '"' || line[i] == '\''))
		// {
		// 	printf(" FUCKING QUOTES TO APPEND!\n");
		// }
	}

}





void	ft_shellfault(t_shell *sh)
{
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line);
}



t_shell	*ft_init_shell(char *envp[])
{
	t_shell	*sh;
	sh = ft_calloc(1, sizeof(t_shell));
	if (!sh)
	{
		printf("Error allocating \"*sh\" struct!\n");
		return (NULL);
	}
	sh->token_lst = NULL;
	sh->envp = envp;

	return (sh);
}



int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*sh;
	int	have_syn_error;

	(void)argc;
	(void)argv;
	sh = ft_init_shell(envp);
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
