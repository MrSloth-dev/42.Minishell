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

int	ft_how_much_consecutives_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_space(str[i]) == TRUE)
		i++;
	return (i);
}

int	ft_append_node(t_token_lst *token_lst, char *str, int type, int status)
{
	t_token	*cur;
	t_token	*new_token;

	cur = NULL;
	new_token = ft_calloc(sizeof(t_token), 1);
	if (!new_token)
		return (0);
	
	new_token->status = status;
	new_token->content = str;
	new_token->type = type;
	new_token->next = NULL;

	if (!token_lst->first)
	{
		token_lst->first = new_token;
		new_token->prev = NULL;
	}
	else if (token_lst->first)
	{
		cur = token_lst->first;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
		new_token->prev = cur;
	}
	return (ft_strlen(str));
}

int	ft_append_word(t_token_lst *token_lst, char *str, int type, int status)
{
	int	len;

	len = 0;
	if (status == NORMAL)
	{
		while (str[len] && ft_is_word(str[len]) == TRUE)
		{
			len++;
		}
		ft_append_node(token_lst, ft_substr(str, 0, len), type, status);
	}
	return(len);
}

void	ft_print_tokens(t_token_lst *token_lst)
{
	t_token	*cur;

	if (!token_lst->first)
		return;
	cur = token_lst->first;
	printf("\ncommand: ");
	while (cur)
	{
		printf("%s", cur->content);
		cur = cur->next;
	}
	cur = token_lst->first;
	printf("\ntypes: ");
	while (cur)
	{
		if (cur->type == WORD)
			printf("WORD ");
		else if (cur->type == WHITE_SPACE)
			printf("ws ");
		else if (cur->type == PIPELINE)
			printf("PIPE ");
		else if (cur->type == HERE_DOC)
			printf("H_DOC ");
		else if (cur->type == REDIR_OUT)
			printf("R_OUT ");
		else if (cur->type == REDIR_IN)
			printf("R_IN ");
		else if (cur->type == DBLE_REDIR_OUT)
			printf("D_R_OUT ");
		else if (cur->type == SINGLE_QTE)
			printf("s_qt ");
		else if (cur->type == DOUBLE_QTE)
			printf("D_qt ");
		cur = cur->next;
	}
	printf("\n");
	cur = token_lst->first;
	printf("STATUS: ");
	while (cur)
	{
		if (cur->status == NORMAL)
			printf("normal ");
		else if (cur->status == IN_DOUBLE_QTE)
			printf("in_DOUBLE_qte ");
		else if (cur->status == IN_SINGLE_QTE)
			printf("in_SINGLE_qte ");
		cur = cur->next;
	}
	printf("\n\n");
}

int	ft_append_inside_quotes(t_token_lst *token_lst, char *str, int status)
{
	int		len;
	char	qte;

	qte = *str;
	len = 1;

	while (str[len] && str[len] != qte)
		len++;
	
	if (len == 1)
		ft_append_node(token_lst, ft_strdup(""), WORD, status);
	else
		ft_append_node(token_lst, ft_substr(str + 1, 0, len - 1), WORD, status);

	return (len + 1);
}


int	ft_append_redir(t_token_lst *token_lst, char *line, int status)
{
	int	i;

	i = 0;

	if (line[i] == '<')
	{
		if (line[i + 1] != 0 && line[i + 1] == '<')
		{
			i += 2;
			i += ft_how_much_consecutives_spaces(line + i);
			i += ft_append_word(token_lst, line + i , HERE_DOC, status);
		}
		else
		{
			i++;
			i += ft_how_much_consecutives_spaces(line + i);
			i += ft_append_word(token_lst, line + i , REDIR_IN, status);
		}
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] != 0 && line[i + 1] == '>')
		{
			i += 2;
			i += ft_how_much_consecutives_spaces(line + i);
			i += ft_append_word(token_lst, line + i , DBLE_REDIR_OUT, status);
		}
		else
		{
			i++;
			i += ft_how_much_consecutives_spaces(line + i);
			i += ft_append_word(token_lst, line + i , REDIR_OUT, status);
		}
	}

	return (i);
}


void ft_join_to_next_token(t_token *cur, t_token *to_join)
{
	char	*str_to_free;

	if (!cur || !to_join)
		return ;
	str_to_free = cur->content;
	cur->content = ft_strjoin(cur->content, to_join->content);
	cur->next = to_join->next;
	if (cur->next)
		cur->next->prev = cur;
	free(to_join->content);
	free(to_join);
	free(str_to_free);
}

void ft_join_tokens(t_token_lst *token_lst)
{
	t_token	*cur;

	if (!token_lst || !token_lst->first)
		return ;
	cur = token_lst->first;
	while (cur)
	{
		if (cur->type == HERE_DOC)
		{
			if (cur->next &&
	   			(cur->next->type == WORD
				|| cur->next->type == IN_SINGLE_QTE
				|| cur->next->type == IN_DOUBLE_QTE))
			{
				ft_join_to_next_token(cur, cur->next);
			}
		}
		cur = cur->next;
	}
	
}


void	ft_tokenizer(t_token_lst *token_lst, char *line)
{
	int	status;
	int	i;

	i = 0;
	status = NORMAL;
	while (line[i])
	{
		if (ft_is_word(line[i]) == TRUE)
		{
			i += ft_append_word(token_lst, line + i, WORD, status);
			if (!line[i])
				break;
		}
		status = ft_check_status(status, line[i]);
		if (status != NORMAL)
		{
			i += ft_append_inside_quotes(token_lst, line + i, status);
			status = NORMAL;
			if (!line[i])
				break ;
		}
		else
		{
			if (ft_is_space(line[i]) == TRUE)
			{
				i += ft_how_much_consecutives_spaces(line + i);
				ft_append_node(token_lst, ft_strdup(" "), WHITE_SPACE, status);
			}
			else if (line[i] == '|')
				i += ft_append_node(token_lst, ft_strdup("|"), PIPELINE, status);
			else if (line[i] == '<' || line[i] == '>')
				i += ft_append_redir(token_lst, line + i, status);
			else if (line[i] == '$')
				i += ft_append_node(token_lst, ft_strdup("$"), ENV, status);
		}
	}
	ft_print_tokens(token_lst);

	//EXPAMD ENVS HERE DARLIN!

	ft_join_tokens(token_lst);

	ft_print_tokens(token_lst);

}

void ft_free_shell(t_shell *sh)
{
	t_token	*cur;
	t_token	*tmp;
	
	if (sh->token_lst && sh->token_lst->first)
	{
		cur = sh->token_lst->first;
		while (cur)
		{
			tmp = cur;
			cur = cur->next;
			free (tmp->content);
			free (tmp);
		}
	}

	free(sh->token_lst);
}



void	ft_shellfault(t_shell *sh)
{
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line);

	ft_free_shell(sh);
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
