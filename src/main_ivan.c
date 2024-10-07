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

void	ft_print_exec(t_token *cur, char *spaces)
{
	t_token	*cmd;
	t_token	*rdir;

	cmd = NULL;
	rdir = NULL;
	if (cur && cur->type != ND_PIPE)
	{
		cmd = cur->left;
		rdir = cur->right;
	}
	while (cmd || rdir)
	{
		ft_printf(1, "%s", spaces);
		if (cmd)
		{
		ft_printf(1, "%s%s ",GREEN, cmd->content);
		cmd = cmd->next;
		}
		else
			ft_printf(1, "       ");
		if (rdir)
		{
			ft_printf(1, "  %s%s%s %d", YELLOW, rdir->content, RED, rdir->type);
			rdir = rdir->next;
		}
		ft_printf(1, "%s\n", RESET);
	}
	if (cur && cur->type == ND_PIPE)
	{
		ft_printf(1, "%s%s          PIPE \n", spaces, RED);
//		ft_print_exec(cur->left, ft_strjoin_free(ft_strdup(""), ft_strdup(spaces)));
//		ft_print_exec(cur->right, ft_strjoin_free(ft_strdup(spaces), ft_strdup("                   ")));
		ft_print_exec(cur->left, "");
		ft_print_exec(cur->right,   "                 ");
	}
}

void	ft_print_binary_tree(t_token_lst *token_lst)
{
	t_token	*cur;

	printf("printing bin tree: \n");
	if (!token_lst && !token_lst->first)
	{
		printf("NO TREE TO PRINT!\n");
		return ;
	}
	cur = token_lst->first;
	ft_print_exec(cur, "");
}

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

t_token	*ft_make_binary_tree(t_token *token, int nd_type)
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
		cur = cur->next;
		tmp->type = ND_PIPE;
		tmp->left = new;
		tmp->left->prev = tmp;
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->right = ft_make_binary_tree(cur, ND_EXEC);
		new = tmp;
	}
	return (new);
}

void	ft_free_tree(t_token_lst *token_lst)
{
	if (token_lst && token_lst->first)
		ft_free_bin_shell(token_lst->first);
	free (token_lst);
}

void	ft_shellfault(t_shell *sh)
{
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line);

//	ft_print_tokens(sh->token_lst);
//	ft_free_lst_shell(sh);

	sh->token_lst->first = ft_make_binary_tree(sh->token_lst->first, ND_EXEC);
	ft_print_binary_tree(sh->token_lst);

	ft_print_binary_tree(sh->token_lst);

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
