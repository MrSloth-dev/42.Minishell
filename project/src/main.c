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

#include "ft_printf.h"
#include "minishell.h"

int	g_rec_signal;

void	ft_tokenizer(t_token_lst *token_lst, char *line, t_shell *sh)
{
	ft_create_tokens(token_lst, line);
	ft_join_heredoc_to_words(token_lst);
	ft_make_expansions(sh);
	ft_split_tokens_with_white_spaces(sh);
	ft_delete_null_expansions_if_needed(sh);
	ft_add_node_exec(token_lst, sh);
	ft_convert_empty_strings(sh->token_lst->first);
	ft_join_tokens(token_lst);
	ft_delete_spaces(token_lst, sh);
	g_rec_signal = 0;
}

void	ft_do_the_parse(t_shell *sh)
{
	ft_tokenizer(sh->token_lst, sh->line, sh);
	ft_check_ambiguous_redir(sh->token_lst->first, sh);
	sh->head = ft_make_bin_tree(sh->token_lst->first);
	ft_do_heredoc_files(sh->token_lst->first, sh);
	ft_run_heredocs(sh->token_lst->first, sh);
	ft_print_ambiguous_redir_msg(sh);
}

void	ft_do_the_execution(t_shell *sh)
{
	int	exit_status;

	if (sh->head && sh->head->type != ND_PIPE
		&& sh->head->left && ft_isbuiltin(sh->head->left->content))
		ft_exec_builtins_parent(sh->head, sh);
	else if (sh->head && sh->head->left)
	{
		if (fork() == 0)
		{
			ft_sig_restore();
			ft_run(sh->head, sh);
		}
		ft_sig_mute();
		waitpid(0, &exit_status, 0);
		ft_sig_restore();
		sh->exit_status = ft_get_exit_status(exit_status, sh);
	}
}

static void	ft_shellfault(t_shell *sh)
{
	if (!sh || !sh->line || sh->line[0] == 0)
		return ;
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_do_the_parse(sh);
	ft_do_the_execution(sh);
	ft_clean_hd_files(sh);
	ft_free_tokens(sh);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*sh;
	int		have_syn_error;

	sh = ft_init_shell(envp, argc, argv, NULL);
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
