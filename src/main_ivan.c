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

// void	ft_print_binary_tree(t_token_lst *token_lst)
// {
// 	t_exec	*cur;
// 	t_token	*cmd;
// 	t_token	*rdir;
//
// 	if (!token_lst || !token_lst->first)
// 		return ;
// 	cur = token_lst->first;
// 	while (cur)
// 	{
//
// 		cur = cur->next;
// 	}
//
// }

// t_token	*ft_new_bin_token()
// {
// 	t_token	*new;
//
// 	new = ft_calloc(sizeof(t_token *), 1);
// 	if (!new)
// 		return (NULL);
// 	new->next = NULL;
// 	new->prev = NULL;
// 	new->left = NULL;
// 	new->right = NULL;
// 	return (new);
// }
//
// void	ft_make_binary_tree(t_token_lst *token_lst)
// {
// 	t_token	*cur;
// 	t_token	*new;
// 	t_token	*cur_left;
// 	t_token	*cur_right;
//
// 	if (!token_lst || !token_lst->first)
// 		return;
// 	new = NULL;
// 	cur = token_lst->first;
//
// 	if (!new)
// 	{
// 		new = ft_new_bin_token();
// 		new->type = ND_EXEC;
// 	}
//
// 	while (cur)
// 	{
// 		if (cur->type == WORD)
// 		{
// 			if (!cur_left)
// 			{
// 			cur_left = cur;
// 			}
// 			else
// 			{
// 				cur_left->next = cur;
// 				cur_left = cur_left->next;
// 			}
// 		}
// 		else  
// 		{
// 			cur_right = cur;
// 			cur_right->next = NULL;
// 		}
// 		cur = cur->next;	
// 	}
// }

void	ft_shellfault(t_shell *sh)
{
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line);
//	ft_make_binary_tree(sh->token_lst);

	ft_free_shell(sh);
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
