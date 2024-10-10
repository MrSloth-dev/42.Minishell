#include "minishell.h"


void	ft_shellfault(t_shell *sh)
{
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1); //this probably need to go to init shell
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line, sh);
	// ft_print_tokens(sh->token_lst); // SEE TOKEN LINKED LIST
	// ft_free_lst_shell(sh); // FREE TOKEN LINKED LIST, ONLY FOR TESTING PURPOSES
	sh->token_lst->first = ft_make_bin_tree(sh->token_lst->first, ND_EXEC);
	// ft_print_binary_tree(sh->token_lst);  // SEE BIN TREE
	if (sh)
		ft_exec_builtins(sh->token_lst->first, sh);
	ft_free_tree(sh->token_lst);
	return;
	
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
			ft_print_syntax_error(have_syn_error); //MAYBE ADD HISTORY HERE
		else
			ft_shellfault(sh);
		free(sh->token_lst);
	}
	return (0);
}
