#include "minishell.h"

void	ft_free_and_exit(t_token *token, t_shell *sh, int exit_flag)
{
	int	exit_status;

	(void)token;
	exit_status = sh->exit_status;
	if (!sh)
		return ;
	sh->line = ft_free(sh->line);

	//ft_free_tree(sh->token_lst);
	ft_free_lst_shell(sh);
	
	sh->token_lst = ft_free(sh->token_lst);
	if (sh->nb_heredoc > 0) // WARNING HERE!!!!!!
		ft_clean_here_doc(sh);
	if (exit_flag == TRUE)
	{
		if (sh->envp)
			sh->envp = ft_free_envp(sh->envp);
		if (sh->path)
			sh->path = ft_free_envp(sh->path);
		sh = ft_free(sh);
		exit (exit_status);
	}
	sh = ft_free(sh);
}

int	ft_invalid_exit_code(t_token *token, t_shell *sh)
{
	int	i;
	int	exit_status;

	if (token && token->next)
	{
		return (sh->exit_status = 1, 1);
	}
	i = 0;
	exit_status = 0;
	if (token->content[i] == '-')
		exit_status = 156;
	if (!ft_isdigit(token->content[0]) || token->content[0] == '+')
		i++;
	while (token && token->content[i])
	{
		if (!ft_isdigit(token->content[i++]))
		{
			ft_printf(STDERR_FILENO, "%s : exit : %s : numeric argument required\n", sh->prog_name, token->content);
			return (sh->exit_status = 2, 2);
		}
	}
	return (exit_status);
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
		sh->exit_status = 1;
		return ;
	}
	else
		sh->exit_status = exit_status;
	ft_printf(STDOUT_FILENO, "exit\n");
	ft_free_and_exit(token, sh, TRUE);
	exit(exit_status);
}
