#include "minishell.h"

void ft_free_bin_shell(t_token	*token)
{
	t_token	*cur;
	t_token	*cur_left;
	t_token	*cur_right;
	t_token	*tmp;

	tmp = NULL;
	cur = NULL;
	cur_left = NULL;
	cur_right = NULL;
	
	if (token && token->type != ND_PIPE)
	{
		cur = token;
		if (cur)
		{
			tmp = cur;
			cur_left = cur->left;
			cur_right = cur->right;
			free (tmp);
		}
		while (cur_left)
		{
			tmp = cur_left;
			cur_left = cur_left->next;
			free(tmp->content);
			free(tmp);
		}
		while (cur_right)
		{
			tmp = cur_right;
			cur_right = cur_right->next;
			free(tmp->content);
			free(tmp);
		}
	}
	else
	{
		cur = token;
		ft_free_bin_shell(cur->left);
		ft_free_bin_shell(cur->right);
		free (cur);
		cur = NULL;
	}
}

void	ft_free_tree(t_token_lst *token_lst)
{
	if (token_lst && token_lst->first)
	{
		ft_free_bin_shell(token_lst->first);
		token_lst->first = NULL; //TAKE CARE OF THIS!
	}

}


void ft_free_lst_shell(t_shell *sh)
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

}

void	*ft_free_envp(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
	envp = NULL;
	return (NULL);
}

void ft_reset_token_lst(t_shell *sh)
{
	if (sh->token_lst)
	{
		free(sh->token_lst);
		sh->token_lst = NULL;
	}
}
