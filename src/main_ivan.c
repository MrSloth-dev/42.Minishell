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

void	ft_print_binary_tree(t_token_lst *token_lst)
{
	t_token	*cur;
	t_token	*cmd;
	t_token	*rdir;

	printf("printing bin tree: \n");
	if (!token_lst && !token_lst->first)
	{
		printf("NO TREE TO PRINT!\n");
		return ;
	}
	cur = token_lst->first;
	cmd = cur->left;
	rdir = cur->right;
	while (cmd || rdir)
	{
		if (cmd)
		{
		printf("%s%s ",GREEN, cmd->content);
		cmd = cmd->next;
		}
		else
			printf("      ");
		if (rdir)
		{
			printf("%s%s %s%d", YELLOW, rdir->content, RED, rdir->type);
			rdir = rdir->next;
		}
		printf("%s\n", RESET);
	}
	printf("\n");
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

void	ft_make_binary_tree(t_token_lst *token_lst)
{
	t_token	*tmp;
	t_token	*cur;
	t_token	*new;
	t_token	*cur_left;
	t_token	*cur_right;

	if (!token_lst || !token_lst->first)
		return;
	cur = token_lst->first;
	new = NULL;
	if (!new)
	{
		new = ft_new_bin_token();
		new->type = ND_EXEC;
	}
	while (cur)
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
	if (new)
		token_lst->first = new;
}

void	ft_prepare_new_prompt(t_shell *sh)
{
	//WARNING - THIS CONTENT IS ONLY FOR TESTING PURPOSES!!!!!!
	
	sh->token_lst = NULL;
	//sh->line = NULL;
}

void	ft_shellfault(t_shell *sh)
{
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line);

//	ft_print_tokens(sh->token_lst);
//	ft_free_lst_shell(sh);

	ft_make_binary_tree(sh->token_lst);
	ft_print_binary_tree(sh->token_lst);
	ft_free_bin_shell(sh);

	//	ft_prepare_new_prompt(sh);
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
