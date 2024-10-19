#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

void	ft_free_and_exit(t_token *token, t_shell *sh, int exit_flag)
{
	int	exit_status;

	(void)token;
	exit_status = sh->exit_status;
	if (!sh)
		return ;
	sh->line = ft_free(sh->line);
	ft_free_tree(sh->token_lst);
	ft_free(sh->token_lst);
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
		sh = ft_free(sh);
		exit (exit_status);
	}
	sh = ft_free(sh);
}

int	ft_invalid_exit_code(t_token *token, t_shell *sh)
{
	int	i;

	if (token && token->next)
	{
		return (sh->exit_status = 1, 1);
	}
	i = 0;
	while (token && token->content[i])
	{
		if (!ft_isdigit(token->content[i++]))
		{
			ft_printf(STDERR_FILENO, "%s : exit : %s : numeric argument required\n", sh->prog_name, token->content);
			return (sh->exit_status = 2, 2);
		}
	}
	return (0);
}

void	ft_exit(t_token *token, t_shell *sh)
{
	int	exit_status;

	if (!token)
	{
		sh->exit_status = 0;
		ft_free_and_exit(token, sh, TRUE);
	}
	exit_status = ft_invalid_exit_code(token, sh);
	if (exit_status == 0)
		sh->exit_status = ft_atoi(token->content);
	else if (exit_status == 1)
	{
		ft_printf(STDOUT_FILENO, "exit\n");
		ft_printf(STDERR_FILENO, "%s : exit : too many arguments\n", sh->prog_name);
		//ft_free_and_exit(token, sh, FALSE);
		return ;
	}
	ft_printf(STDOUT_FILENO, "exit\n");
	ft_free_and_exit(token, sh, TRUE);
	exit(sh->exit_status);
}
