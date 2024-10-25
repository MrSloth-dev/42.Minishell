/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:04:52 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 13:16:57 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_rec_signal;

void	ft_tokenizer(t_token_lst *token_lst, char *line, t_shell *sh)
{
	ft_create_tokens(token_lst, line);
	ft_make_expansions(sh);
	ft_join_tokens(token_lst);
	ft_delete_spaces(token_lst, sh);
	ft_add_node_exec(token_lst, sh);
	g_rec_signal = 0;
}

void	ft_shellfault(t_shell *sh)
{
	int		exit_status;

	if (!sh || !sh->line || sh->line[0] == 0)
		return ;
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line, sh);
	sh->head = ft_make_bin_tree(sh->token_lst->first);
	ft_do_heredoc_files(sh->token_lst->first, sh);
	ft_print_data(sh, PRINT_DATA); //REMOVE BEFORE DELIVER
	ft_create_and_run_heredocs(sh);
	if (sh->head && sh->head->type != ND_PIPE
		&& sh->head->left && ft_isbuiltin(sh->head->left->content))
		ft_exec_builtins_parent(sh->head, sh);
	else if (sh->head && sh->head->left)
	{
		if (fork() == 0)
			ft_run_cmd(sh->head, sh);
		waitpid(0, &exit_status, 0);
		sh->exit_status = WEXITSTATUS(exit_status);
	}
	ft_clean_hd_files(sh);
	ft_free_tokens(sh);
	sh->nb_heredoc = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*sh;
	int		have_syn_error;

	(void)argc;
	sh = ft_init_shell(envp, argv[0]);
	while (1)
	{
		ft_readline(sh);
		have_syn_error = ft_have_syntax_error(sh);
		if (have_syn_error != FALSE)
			ft_print_syntax_error(have_syn_error, sh);
		else
			ft_shellfault(sh);
	}
	return (0);
}
