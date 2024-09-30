#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

void	ft_update_oldpwd(char *old_pwd, t_shell *shell);

void	ft_cd(char **cmdargs, t_shell *shell)
{
	char *old_pwd;
	char *update_old_pwd;

	if (cmdargs[0]) // error checking
	{
		if (cmdargs[1][0])
			return ;
		if (cmdargs[2])
			return ; // too many args
	}
	update_old_pwd = getcwd(NULL, 0);
	if (!ft_strncmp("--", cmdargs[1], 2)) // change to home
		{
			old_pwd = ft_get_env("HOME", shell);
			chdir(old_pwd);
		}
	else if (!ft_strncmp("-", cmdargs[1], 1)) // print old pwd and change to it
		{
			old_pwd = ft_get_env("HOME", shell);
			ft_printf(1, "%s\n", old_pwd);
			chdir(old_pwd);
		}
	else if (!ft_strncmp("~", cmdargs[1], 1))
		chdir(ft_get_env("HOME", shell));
	ft_update_oldpwd(update_old_pwd, shell);
}

void	ft_update_oldpwd(char *old_pwd, t_shell *shell)
{
	char *old_pwd_str;
	int		j;

	old_pwd_str = ft_strjoin_free(ft_strdup("OLDPWD="), old_pwd);
	j = -1;
	if (ft_env_exist(old_pwd_str, &j, shell->envp) == -1)
		ft_append_env(old_pwd_str, shell->envp);
	else
		ft_swap_env(old_pwd_str, shell->envp, j);
	free(old_pwd);
	free(old_pwd_str);
}
