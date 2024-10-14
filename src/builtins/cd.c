#include "minishell.h"
#include <unistd.h>

void	ft_safe_chdir(char *path, t_shell *shell, int flags);
void	ft_update_directory(char *path, char *variable, t_shell *shell);

void	ft_change_home(t_token *cmdargs, t_shell *shell)
{
	char	*home;
	char	*old_home;

	if (!cmdargs || !strcmp(cmdargs->content, "--"))
	{
		old_home = getcwd(NULL, 0);
		ft_update_directory(old_home, "OLDPWD=", shell);
		home = ft_get_env_value("HOME", shell->envp, shell);
		ft_safe_chdir(home, shell, 0);
		ft_update_directory(home, "PWD=", shell);
		free (old_home);
	}
	else if (!strcmp(cmdargs->content, "~"))
	{
		home = ft_get_env_value("HOME", shell->envp, shell);
		ft_safe_chdir(home, shell, 0);
		ft_update_directory(home, "PWD=", shell);
	}
}

void	ft_cd(t_token *cmdargs, t_shell *shell)
{
	char	*update_old;
	char	*old_pwd;

	if (cmdargs)
	{
		if (!cmdargs->content[0])
			return ;
		if (cmdargs->next)
			return (ft_safe_chdir(NULL, shell, 2));
	}
	update_old = getcwd(NULL, 0);
	if (!cmdargs || !ft_strcmp(cmdargs->content, "~\0")
		|| !ft_strcmp(cmdargs->content, "--"))
		ft_change_home(cmdargs, shell);
	else if (!ft_strcmp(cmdargs->content, "-"))
	{
		old_pwd = ft_get_env_value("OLDPWD", shell->envp, shell);
		ft_printf(STDOUT_FILENO, "%s\n", old_pwd);
		ft_safe_chdir(old_pwd, shell, 0);
	}
	else
		ft_safe_chdir(cmdargs->content, shell, 0);
	ft_update_directory(update_old, "OLDPWD=", shell);
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
	shell->exit_status = EXIT_SUCCESS;
	ft_update_directory(getcwd(NULL, 0), "PWD=", shell);
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
