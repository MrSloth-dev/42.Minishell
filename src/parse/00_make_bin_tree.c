#include "minishell.h"

t_token	*ft_new_bin_token()
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_token	*ft_make_bin_tree(t_token *token)
{
	t_iter	s;

	if (!token || !token->front)
		return (NULL);
	s = ft_set_iter(0);
	s.cur = token->front;
	while (s.cur && s.cur->type != ND_PIPE)
	{
		if (s.cur->type == WORD && s.cur->type != ND_EXEC)
		{
			if (!token->left)
			{
				token->left = s.cur;
				s.cur_left = s.cur;
			}
			else
			{
				s.cur->prev = s.cur_left;
				s.cur->prev->next = s.cur;
				s.cur_left = s.cur_left->next;
			}
		}
		else if (s.cur->type != ND_EXEC)
		{
			if (!token->right)
			{
				token->right = s.cur;
				s.cur_right = s.cur;
			}
			else
			{
				s.cur->prev = s.cur_right;
				s.cur->prev->next = s.cur;
				s.cur_right = s.cur_right->next;
			}
		}
		s.cur = s.cur->front;
	}
	if (s.cur && s.cur->type == ND_PIPE)
	{
		//s.cur->content = ft_free(s.cur->content);
		s.cur->left = token;
		//s.tmp->left->prev = s.tmp;
		s.cur->right = ft_make_bin_tree(s.cur->front);
		token = s.cur;
	}
	return (token);
}
