#include "minishell.h"

void	ft_exec_builtins(t_token *cmdargs, t_shell *shell)
{
	if (ft_strcmp("cd", cmdargs->content) == 0)
		ft_cd(cmdargs, shell);
	else if (ft_strcmp("env", cmdargs->content) == 0)
		ft_env(shell);
	else if (ft_strcmp("pwd", cmdargs->content) == 0)
		ft_pwd(shell);
	else if (ft_strcmp("echo", cmdargs->content) == 0)
		ft_echo(cmdargs, shell);
	// else if (ft_strcmp("export", cmdargs[0]) == 0)
	// 	ft_export(cmdargs, shell);
	// else if (ft_strcmp("unset", cmdargs[0]) == 0)
	// 	ft_unset(cmdargs, shell);
	// else if (ft_strcmp("exit", cmdargs[0]) == 0)
	// 	ft_exit(NULL, shell);
}
