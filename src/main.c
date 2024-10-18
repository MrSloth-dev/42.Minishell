#include "minishell.h"

	// ft_print_tokens(sh->token_lst); // SEE TOKEN LINKED LIST
	// ft_free_lst_shell(sh); // FREE TOKEN LINKED LIST, ONLY FOR TESTING PURPOSES
	//ft_print_binary_tree(sh->token_lst);  // SEE BIN TREE
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
	t_token	*head;

	if (!sh || !sh->line || sh->line[0] == 0)
		return ;
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line, sh);
	sh->token_lst->first = ft_make_bin_tree(sh->token_lst->first, ND_EXEC);

	if (sh->nb_heredoc > 0)
		ft_create_and_run_heredocs(sh);

	head = sh->token_lst->first;
	if (!head)
		return ;
	if (head->type != ND_PIPE && head->left && ft_isbuiltin(head->left->content))
		ft_exec_builtins_parent(sh->token_lst->first, sh);
	else if (head->left)
	{
		if (fork() == 0)
			ft_run_cmd(sh->token_lst->first, sh);
		wait(0);
	}
	ft_free_tree(sh->token_lst);
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
			ft_print_syntax_error(have_syn_error); //MAYBE ADD HISTORY HERE
		else
			ft_shellfault(sh);
	}
	return (0);
}
