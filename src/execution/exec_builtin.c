#include "minishell.h"

void	ft_exec_builtins(t_token *cmdargs, t_shell *shell)
{
	t_token	*tempnext;

	tempnext = NULL;
	if (cmdargs)
	{
		cmdargs = cmdargs->left;
		if (cmdargs && cmdargs->next)
			tempnext = cmdargs->next;
		if (ft_strcmp("cd", cmdargs->content) == 0)
			ft_cd(tempnext, shell);
		else if (ft_strcmp("env", cmdargs->content) == 0)
			ft_env(shell);
		else if (ft_strcmp("pwd", cmdargs->content) == 0)
			ft_pwd(shell);
		else if (ft_strcmp("echo", cmdargs->content) == 0)
			ft_echo(tempnext, shell);
		else if (ft_strcmp("export", cmdargs->content) == 0)
			ft_export(tempnext, shell);
		else if (ft_strcmp("unset", cmdargs->content) == 0)
		 	ft_unset(tempnext, shell);
		else
			ft_execute_command(cmdargs, shell);
		// else if (ft_strcmp("exit", cmdargs[0]) == 0)
		// 	ft_exit(NULL, shell);
	}
}
