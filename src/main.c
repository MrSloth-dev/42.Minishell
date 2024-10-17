#include "minishell.h"
#include <unistd.h>

int	ft_isbuiltin(char *content)
{
	if (!ft_strcmp(content, "echo"))
		return (1);
	else if (!ft_strcmp(content, "cd"))
		return (1);
	else if (!ft_strcmp(content, "pwd"))
		return (1);
	else if (!ft_strcmp(content, "export"))
		return (1);
	else if (!ft_strcmp(content, "unset"))
		return (1);
	else if (!ft_strcmp(content, "env"))
		return (1);
	else if (!ft_strcmp(content, "exit"))
		return (1);
	else
		return (0);
}

void ft_reset_token_lst(t_shell *sh)
{
	if (sh->token_lst)
	{
		free(sh->token_lst);
		sh->token_lst = NULL;
	}
}





void	ft_make_heredoc_fd(int nb_heredoc, t_shell *sh)
{


	sh->heredoc_fd = ft_calloc(sizeof(int),  nb_heredoc + 1);
	if (!sh->heredoc_fd)
		ft_printf(1, "NEED TO DO SOMETHING HERE LIKE FREE MEM\n");
	sh->heredoc_fd[nb_heredoc] = -1;



	int i = 0;
	ft_printf(1, "nb_heredoc: %d\n", sh->nb_heredoc);
	while (i < nb_heredoc + 1)
		ft_printf(1, "%d, ", sh->heredoc_fd[i++]);
	ft_printf(1, "\n");
}






	// ft_print_tokens(sh->token_lst); // SEE TOKEN LINKED LIST
	// ft_free_lst_shell(sh); // FREE TOKEN LINKED LIST, ONLY FOR TESTING PURPOSES
	//ft_print_binary_tree(sh->token_lst);  // SEE BIN TREE
void	ft_shellfault(t_shell *sh)
{
	t_token	*head;

	if (!sh || !sh->line || sh->line[0] == 0)
		return ;
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line, sh);

	if (sh->nb_heredoc > 0)
		ft_make_heredoc_fd(sh->nb_heredoc, sh);




	sh->token_lst->first = ft_make_bin_tree(sh->token_lst->first, ND_EXEC);
	head = sh->token_lst->first;
	if (!head)
		return ;
	if (head->type != ND_PIPE && ft_isbuiltin(head->left->content))
		ft_exec_builtins_parent(sh->token_lst->first, sh);
	else
	{
		if (fork() == 0)
			ft_run_cmd(sh->token_lst->first, sh);
		wait(0);
	}
	ft_free_tree(sh->token_lst);
	ft_reset_token_lst(sh);
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
		// if (sh->token_lst)
		// 	free(sh->token_lst);
	}
	return (0);
}
