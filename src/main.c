#include "minishell.h"

int	g_rec_signal;

void	ft_add_node_exec(t_token_lst *token_lst, t_shell *sh)
{
	t_iter	h;
	t_token *exec_node;

	if (!token_lst || !token_lst->first || !sh)
		return ;
	h = ft_set_iter(0);
	h.cur = token_lst->first->front;
	while (h.cur)
	{
		h.tmp = h.cur;
		h.cur = h.cur->front;
		if (h.tmp->type == ND_PIPE && h.cur)
		{
			exec_node = ft_new_token();
			if (!exec_node)
				return ;
			exec_node->type = ND_EXEC;
			exec_node->content = ft_strdup("ND_EXEC ");
			h.cur->back = exec_node;
			exec_node->front = h.cur;
			h.tmp->front = exec_node;
			exec_node->back = h.tmp;
		}
	}
}

void	ft_tokenizer(t_token_lst *token_lst, char *line, t_shell *sh)
{
	ft_create_tokens(token_lst, line);
	ft_make_expansions(sh);
	ft_join_tokens(token_lst);
	ft_delete_space_and_count_hd(token_lst, sh);
	ft_add_node_exec(token_lst, sh);
	g_rec_signal = 0;
}

void	ft_clean_here_doc(t_shell *sh)
{
	char *name;

	while (sh->nb_heredoc--)
	{
		name = ft_itoa(sh->nb_heredoc);
		unlink(name);
		free(name);
	}
	free(sh->heredoc_fd);
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

	ft_print_data(sh, PRINT_DATA);

	if (sh->nb_heredoc > 0)
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

	ft_free_lst_shell(sh);
	ft_reset_token_lst(sh);

	if (sh->nb_heredoc > 0) // WARNING HERE!!!!!!
		ft_clean_here_doc(sh);
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
			ft_print_syntax_error(have_syn_error, sh); //MAYBE ADD HISTORY HERE
		else
			ft_shellfault(sh);
	}
	return (0);
}
	// ft_free_lst_shell(sh); // FREE TOKEN LINKED LIST, ONLY FOR TESTING PURPOSES
	//ft_print_binary_tree(sh->token_lst);  // SEE BIN TREE
