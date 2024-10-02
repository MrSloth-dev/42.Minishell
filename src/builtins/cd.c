#include "minishell.h"

#include <unistd.h>

void	ft_safe_chdir(char *path, t_shell *shell, int flags);
void	ft_update_directory(char *path, char *variable, t_shell *shell);

void	ft_change_home(t_shell *shell)
{
	char	*home;

	home = ft_get_env_value("HOME", shell);
	ft_update_directory(getcwd(NULL, 0), "OLDPWD=", shell);
	ft_update_directory(home, "PWD=", shell);
	ft_safe_chdir(home, shell, 0);
}

void	ft_cd(char **cmdargs, t_shell *shell)
{
	// if (cmdargs[2])
		// ft_safe_chdir(NULL, t_shell *shell, int flags)
	if (!cmdargs[1] || cmdargs[1][0] == '~' || (cmdargs[1][0] == '-'
		&& cmdargs[1][1] == '-'))
		ft_change_home(shell);
	else if (cmdargs[1][0] == '~')
		ft_change_home(shell);
	return ;
}

void	ft_safe_chdir(char *path, t_shell *shell, int flags)
{
	if (flags == 2)
	{
		ft_printf(STDERR_FILENO, "cd : too many args");
		return ;
	}
	if (chdir(path) == -1)
	{
		if (flags == 1)
			ft_printf(STDERR_FILENO, "cd : HOME not set");
		else
			ft_printf(STDERR_FILENO, "cd : %s: No such file or directory",
				path);
		shell->exit_status = EXIT_FAILURE;
	}
	shell->exit_status = EXIT_SUCCESS;
}

void	ft_update_directory(char *path, char *variable, t_shell *shell)
{
	char	*path_str;
	int		j;

	path_str = ft_strjoin(variable, path);
	j = -1;
	if (ft_env_exist(path_str, &j, shell->envp) == -1)
		ft_append_env(path_str, shell->envp);
	else
		ft_swap_env(path_str, shell->envp, j);
	ft_printf(1, "%s currentyl is %s\n", variable, path);
	free(path_str);
}
