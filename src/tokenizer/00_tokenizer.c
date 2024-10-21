#include "minishell.h"

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
	new_token->hd_id = -1;

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
			len++;

		ft_append_node(token_lst, ft_substr(str, 0, len), type, status);
	}
	return(len);
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

static void	ft_append_redir_in(t_token_lst *token_lst, t_iter *h)
{	
	if (h->line[h->i + 1] && h->line[h->i + 1] == '<')
	{
		h->i += ft_how_much_consecutives_spaces(h->line + h->i + 2) + 2;
		h->i += ft_append_word(token_lst, h->line + h->i, HERE_DOC, h->status);
	}
	else
	{
		h->i += ft_how_much_consecutives_spaces(h->line + h->i + 1) + 1;
		h->i += ft_append_word(token_lst, h->line + h->i, REDIR_IN, h->status);
	}
}

static void	ft_append_redir_out(t_token_lst *token_lst, t_iter *h)
{
	if (h->line[h->i + 1] && h->line[h->i + 1] == '>')
	{
		h->i += ft_how_much_consecutives_spaces(h->line + h->i + 2) + 2;
		h->i += ft_append_word(token_lst, h->line + h->i, DBLE_REDIR_OUT, h->status);
	}
	else
	{
		h->i += ft_how_much_consecutives_spaces(h->line + h->i + 1) + 1;
		h->i += ft_append_word(token_lst, h->line + h->i, REDIR_OUT, h->status);
	}
}

int	ft_append_redir(t_token_lst *token_lst, char *line, int status)
{
	t_iter	h;

	if (!line || !token_lst)
		return (0);
	h = ft_set_iter(0);
	h.line = line;
	h.c = line[0];
	h.status = status;
	if (h.c == '<')
		ft_append_redir_in(token_lst, &h);
	else if (h.c == '>')
		ft_append_redir_out(token_lst, &h);
	return (h.i);
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

	if (!token_lst && !token_lst->first)
		return ;
	cur = token_lst->first;
	while (cur)
	{
			if (cur->type == WORD || cur->type == HERE_DOC)
			{
				while (cur->next && (cur->next->type == WORD))
					ft_join_to_next_token(cur, cur->next);
			}
		cur = cur->next;
	}
}

void	ft_delete_space_tokens_and_count_heredoc(t_token_lst *token_lst, t_shell *sh)
{
	t_token	*cur;
	t_token	*tmp;

	if (!token_lst || !token_lst->first)
		return ;
	cur = token_lst->first;
	while (cur)
	{
		if (cur->type == WHITE_SPACE)
		{
			tmp = cur;
			cur = cur->next;
			if (cur)
				cur->prev = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = cur;
			free(tmp->content);
			free(tmp);
			continue ;
		}
		else if (cur->type == HERE_DOC)
		{
			cur->hd_id = sh->nb_heredoc;
			sh->nb_heredoc++;
			cur = cur->next;
		}
		else
			cur = cur->next;
	}
}

void	ft_tokenizer(t_token_lst *token_lst, char *line, t_shell *sh)
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
		}
	}


	ft_make_expansions(sh);

	ft_join_tokens(token_lst);
	ft_delete_space_tokens_and_count_heredoc(token_lst, sh);
	g_rec_signal = 0;

	//ft_print_tokens(token_lst);
}
