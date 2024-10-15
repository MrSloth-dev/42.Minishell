#include "minishell.h"
#include <unistd.h>

int	ft_isbuiltin(char *content)
{
	if (!ft_strcmp(content, "exit"))
		return (1);
	else if (!ft_strcmp(content, "env"))
		return (1);
	else if (!ft_strcmp(content, "pwd"))
		return (1);
	else if (!ft_strcmp(content, "export"))
		return (1);
	else if (!ft_strcmp(content, "echo"))
		return (1);
	else if (!ft_strcmp(content, "unset"))
		return (1);
	else if (!ft_strcmp(content, "cd"))
		return (1);
	else
		return (0);
}

	// ft_print_tokens(sh->token_lst); // SEE TOKEN LINKED LIST
	// ft_free_lst_shell(sh); // FREE TOKEN LINKED LIST, ONLY FOR TESTING PURPOSES
	//ft_print_binary_tree(sh->token_lst);  // SEE BIN TREE
void	ft_shellfault(t_shell *sh)
{
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line, sh);
	sh->token_lst->first = ft_make_bin_tree(sh->token_lst->first, ND_EXEC);
	if (!sh->token_lst->first)
		return ;
	if (fork() == 0)
		ft_run_cmd(sh->token_lst->first, sh);
	wait(0);
	// ft_free_tree(sh->token_lst);
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
		// if (sh->token_lst)
		// 	free(sh->token_lst);
	}
	return (0);
}
