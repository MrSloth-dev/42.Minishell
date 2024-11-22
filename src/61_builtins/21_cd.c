/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:18:50 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/29 12:26:44 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_safe_chdir(char *path, t_shell *shell, int flags);
static void	ft_update_directory(char *path, char *variable, t_shell *shell);

static void	ft_change_home(t_token *cmdargs, t_shell *shell)
{
	char	*home;
	char	*old_home;

	if (!cmdargs || !ft_strcmp(cmdargs->content, "--"))
	{
		old_home = getcwd(NULL, 0);
		ft_update_directory(old_home, "OLDPWD=", shell);
		home = ft_get_env_value("HOME", shell->envp, shell);
		if (!*home)
			ft_safe_chdir(home, shell, 1);
		else
			ft_safe_chdir(home, shell, 0);
		ft_update_directory(home, "PWD=", shell);
		free (old_home);
	}
	else if (!ft_strcmp(cmdargs->content, "~"))
	{
		home = getenv("HOME");
		ft_safe_chdir(home, shell, 0);
		ft_update_directory(home, "PWD=", shell);
	}
}

static void	ft_old_pwd(t_shell *shell)
{
	char	*old_pwd;

	old_pwd = ft_get_env_value("OLDPWD", shell->envp, shell);
	if (old_pwd && *old_pwd)
	{
		ft_printf(STDOUT_FILENO, "%s\n", old_pwd);
		ft_safe_chdir(old_pwd, shell, 0);
	}
	else
		ft_printf(STDOUT_FILENO, "%s: cd: OLDPWD not set\n", shell->prog_name);
}

void	ft_cd(t_token *cmdargs, t_shell *shell)
{
	char	*update_old;

	if (cmdargs)
	{
		if (!cmdargs->content[0])
			return ;
		if (cmdargs->next)
			return (ft_safe_chdir(NULL, shell, 2));
	}
	update_old = getcwd(NULL, 0);
	if (!cmdargs || !ft_strcmp(cmdargs->content, "~")
		|| !ft_strncmp(cmdargs->content, "--", 2))
		ft_change_home(cmdargs, shell);
	else if (!ft_strcmp(cmdargs->content, "-"))
		ft_old_pwd(shell);
	else
		ft_safe_chdir(cmdargs->content, shell, 0);
	ft_update_directory(update_old, "OLDPWD=", shell);
	ft_free(update_old);
}

static void	ft_safe_chdir(char *path, t_shell *shell, int flags)
{
	char	*pwd;

	if (flags == 2)
	{
		ft_printf(STDERR_FILENO, "cd : too many arguments\n");
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	else if (chdir(path) == -1)
	{
		if (flags == 1)
			ft_printf(STDERR_FILENO, "cd : HOME not set\n");
		else
			ft_printf(STDERR_FILENO, "cd : %s: No such file or directory\n",
				path);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	shell->exit_status = EXIT_SUCCESS;
	pwd = getcwd(NULL, 0);
	ft_update_directory(pwd, "PWD=", shell);
	pwd = ft_free(pwd);
}

static void	ft_update_directory(char *path, char *variable, t_shell *shell)
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
	path_str = ft_free(path_str);
}
