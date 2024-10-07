#include "minishell.h"

void ft_free_shell(t_shell *sh)
{
	//THIS NOT WORKS ON BINARY TREE!!!!!!!
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
