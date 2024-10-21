#include "minishell.h"

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

void	ft_join_tokens(t_token_lst *token_lst)
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

void	ft_delete_space_and_count_hd(t_token_lst *token_lst, t_shell *sh)
{
	t_iter	s;

	if (!token_lst || !token_lst->first)
		return ;
	s.cur = token_lst->first;
	while (s.cur)
	{
		s.tmp = s.cur;
		s.cur = s.cur->next;
		if (s.tmp->type == WHITE_SPACE)
		{
			if (s.cur)
				s.cur->prev = s.tmp->prev;
			if (s.tmp->prev)
				s.tmp->prev->next = s.cur;
			free(s.tmp->content);
			free(s.tmp);
			continue ;
		}
		else if (s.tmp->type == HERE_DOC)
		{
			s.tmp->hd_id = sh->nb_heredoc;
			sh->nb_heredoc++;
		}
	}
}

void	ft_create_tokens(t_token_lst *token_lst, char *line)
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
}


void	ft_tokenizer(t_token_lst *token_lst, char *line, t_shell *sh)
{
	ft_create_tokens(token_lst, line);
	ft_make_expansions(sh);
	ft_join_tokens(token_lst);
	ft_delete_space_and_count_hd(token_lst, sh);
	g_rec_signal = 0;
}
