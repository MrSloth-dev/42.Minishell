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

t_token	*ft_make_bin_tree(t_token *token, int nd_type)
{
	t_token	*tmp;
	t_token	*cur;
	t_token	*new;
	t_token	*cur_left;
	t_token	*cur_right;

	if (!token)
		return (NULL);
	cur = token;
	new = NULL;
	if (!new)
	{
		new = ft_new_bin_token();
		new->type = nd_type;
	}
	while (cur && cur->type != PIPELINE)
	{
		tmp = cur;
		cur = cur->next;
		if (tmp->type == WORD)
		{
			if (!new->left)
			{
				new->left = tmp;
				tmp->next = NULL;
				tmp->prev = new;
				cur_left = tmp;
			}
			else
			{
				cur_left->next = tmp;
				tmp->next = NULL;
				tmp->prev = cur_left;
				cur_left = cur_left->next;
			}
		}
		else
		{
			if (!new->right)
			{
				new->right = tmp;
				tmp->next = NULL;
				tmp->prev = new;
				cur_right = tmp;
			}
			else
			{
				cur_right->next = tmp;
				tmp->next = NULL;
				tmp->prev = cur_right;
				cur_right = cur_right->next;
			}
		}
	}
	if (cur && cur->type == PIPELINE)
	{
		tmp = cur;
		free (cur->content);
		cur = cur->next;
		tmp->type = ND_PIPE;
		tmp->left = new;
		tmp->left->prev = tmp;
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->right = ft_make_bin_tree(cur, ND_EXEC);
		new = tmp;
	}
	return (new);
}
