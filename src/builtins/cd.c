#include "minishell.h"

void	ft_safe_chdir(char *path, t_shell *shell, int flags);
void	ft_update_directory(char *path, char *variable, t_shell *shell);

void	ft_change_home(char **cmdargs, t_shell *shell)
{
	char	*home;

	if (!cmdargs[1] || !strcmp(cmdargs[1], "--"))
	{
		ft_update_directory(getcwd(NULL, 0), "OLDPWD=", shell);
		home = ft_get_env_value(ft_strdup("HOME"), shell->envp, shell);
		ft_safe_chdir(home, shell, 0);
	}
	else if (!strcmp(cmdargs[1], "~"))
	{
		home = ft_get_env_value(ft_strdup("HOME"), shell->envp, shell);
		ft_safe_chdir(home, shell, 0);
	}

}

void	ft_cd(char **cmdargs, t_shell *shell)
{
	char	*update_old;
	char	*old_pwd;

	if (cmdargs[1])
	{
		if (!cmdargs[1][0])
			return ;
		if (cmdargs[2])
			return (ft_safe_chdir(NULL, shell, 2));
	}
	update_old = getcwd(NULL, 0);
	if (!cmdargs[1] || !ft_strcmp(cmdargs[1], "~") || !ft_strcmp(cmdargs[1], "--"))
		ft_change_home(cmdargs, shell);
	else if (cmdargs[1][0] == '-')
	{
		old_pwd = ft_get_env_value("OLDPWD", shell->envp, shell);
		ft_printf(STDOUT_FILENO, "%s\n", old_pwd);
		ft_safe_chdir(old_pwd, shell, 0);
		free(old_pwd);
	}
	else
		ft_safe_chdir(cmdargs[1], shell, 0);
	ft_printf(STDOUT_FILENO, "PWD currently is %s\n",
		ft_get_env_value("PWD", shell->envp, shell));
	ft_printf(STDOUT_FILENO, "OLDPWD currently is %s\n",
		ft_get_env_value("OLDPWD", shell->envp, shell));
	return ;
}

void	ft_safe_chdir(char *path, t_shell *shell, int flags)
{
	if (flags == 2)
	{
		ft_printf(STDERR_FILENO, "cd : too many args");
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	else if (chdir(path) == -1)
	{
		if (flags == 2)
			ft_printf(STDERR_FILENO, "cd : HOME not set\n");
		else
			ft_printf(STDERR_FILENO, "cd : %s: No such file or directory\n",
				path);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	ft_update_directory(getcwd(NULL, 0), "PWD", shell);
	shell->exit_status = EXIT_SUCCESS;
}

void	ft_update_directory(char *path, char *variable, t_shell *shell)
{
	char	*path_str;
	int		j;

	if (!path || !variable)
		return ; 
	path_str = ft_strjoin(variable, path);
	j = -1;
	if (ft_env_exist(path_str, &j, shell->envp) == -1)
		ft_append_env(path_str, shell->envp);
	else
		ft_swap_env(path_str, shell->envp, j);
	free(path_str);
}
