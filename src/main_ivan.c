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




void	ft_shellfault(t_shell *sh)
{
	ft_exec_builtins(ft_split(sh->line, ' '), sh);
	return;
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line);

	ft_print_tokens(sh->token_lst); // SEE TOKEN LINKED LIST
//	ft_free_lst_shell(sh); // FREE TOKEN LINKED LIST, ONLY FOR TESTING PURPOSES

	sh->token_lst->first = ft_make_bin_tree(sh->token_lst->first, ND_EXEC);

	ft_print_binary_tree(sh->token_lst);  // SEE BIN TREE
	//execution is made here
	ft_free_tree(sh->token_lst);
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
