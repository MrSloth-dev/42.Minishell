#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

void	ft_free_and_exit(t_token *token, t_shell *sh, int exit_flag)
{
	(void)token;
	if (!sh)
		return ;
	if (sh->line)
	{
		free(sh->line);
		sh->line = NULL;
	}
	ft_free_tree(sh->token_lst);
	if (sh->token_lst)
	{
		free(sh->token_lst);
		sh->token_lst = NULL;
	}
	if (sh->nb_heredoc > 0) // WARNING HERE!!!!!!
		ft_clean_here_doc(sh);
	if (exit_flag == TRUE)
	{
		if (sh->envp)
		{
			ft_free_envp(sh->envp);
			sh->envp = NULL;
		}
		if (sh->path)
		{
			ft_free_envp(sh->path);
			sh->path = NULL;
		}
		free(sh);
		exit (EXIT_SUCCESS);
	}
	free(sh);
}

void	ft_exit(t_token *token, t_shell *shell)
{
	ft_printf(STDOUT_FILENO, "exit\n");
	ft_free_and_exit(token, shell,TRUE);
}
