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

int	ft_how_much_consecutive_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_is_space(str[i]) == TRUE)
		i++;
	printf("consecutive %d spaces\n", i);
	return (i);
}

void	ft_append_node(t_token_lst *token_lst, char *str, int type)
{
	(void)token_lst;
	(void)str;
	(void)type;
//	printf("      APPEND WORD\n");
}

int	ft_append_word(t_token_lst *token_lst, char *str, int type)
{
	int	j;

	(void)token_lst;
	j = 0;
	if (type == WORD)
	{
		while (ft_is_word(str[j]) == TRUE)
			j++;
	}
	return(j);
}

void	ft_tokenizer(t_token_lst *token_lst, char *line)
{
//	int	status;
	int	i;

//	status = NORMAL;
	i = -1;
	while (line[++i])
	{
//		if (status == NORMAL)
//		{
		if (ft_is_word(line[i]) == TRUE)
		{
			i += ft_append_word(token_lst, line + i, WORD) - 1;
			if (!line[i])
				break ;
		}
		else if (ft_is_space(line[i]) == TRUE)
			i += ft_how_much_consecutive_spaces(line + i) - 1;
		else if (line[i] == '|')
		{
			printf("\nhere is a PIPE\n\n");
		}
		else if (line[i] == '$')
		{
			printf("Oh my god, here is a DOLLAR! lets check heredoc!\n");
		}
		else if (line[i] == '<' || line[i] == '>')
		{
			printf("\nthere is a redir\n\n");
		}
		else if ((line[i] == '"' || line[i] == '\''))
		{
			printf(" FUCKING QUOTES TO APPEND!\n");
		}
//		}
	}
}

void	ft_shellfault(t_shell *sh)
{
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
	sh->envp = envp;
	sh->token_lst = NULL;
	return (sh);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = ft_init_shell(envp);
	while (1)
	{
		ft_readline(sh);
		if (ft_have_syntax_error(sh) != FALSE)
			ft_print_syntax_error(ft_have_syntax_error(sh));
		else
			ft_shellfault(sh);
	}
	return (0);
}
