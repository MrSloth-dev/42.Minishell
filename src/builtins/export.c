#include "minishell.h"

void	ft_join_env(char *cmdargs, char **temp, int j)
{
	int		k;
	char	*start;

	start = NULL;
	k = 0;
	j--;
	while (temp[k])
	{
		if (j == k)
		{
			start = ft_strchr(&cmdargs[k], '=');
			temp[k] = ft_strjoin(temp[k], ++start);
		}
		if (!temp[k])
			return ;
		k++;
	}
}

static int	ft_export_duplicate(char **cmdargs, int k)
{
	char	*temp;

	temp = cmdargs[k];
	while (--k)
		if (cmdargs[k] == temp)
			return (1);
	return (0);
}

static int	ft_export_size_increase(char **cmdargs, t_shell *shell, int *j)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	*j = -1;
	while (shell->envp[i])
		i++;
	while (cmdargs[k])
	{
		if (ft_env_exist(cmdargs[k], j, shell->envp) == -1
			&& !ft_strchr(cmdargs[k], '='))
			i++;
		if (ft_export_duplicate(cmdargs, k))
			i--;
		k++;
	}
	return (i);
}

int	ft_plus_mode(char *cmdargs)
{
	int	i;

	i = 0;
	while (cmdargs[i] && cmdargs[i] != '=')
		if (cmdargs[i++] == '+')
			return (1);
	return (0);
}

void	ft_add_env(char **cmdargs, char **temp, int plus_mode, t_shell *shell)
{
	int	j;
	int	k;

	j = -1;
	k = 0;
	while (cmdargs[++k])
	{
		if (!ft_strchr(cmdargs[k], '='))
			continue ;
		plus_mode = ft_plus_mode(cmdargs[k]);
		if (ft_env_exist(cmdargs[k], &j, temp) != -1 && plus_mode)
			ft_swap_plus_env(cmdargs[k], temp, j, shell);
		else if (ft_env_exist(cmdargs[k], &j, temp) != -1 && !plus_mode)
			ft_swap_env(cmdargs[k], temp, j);
		else
			ft_append_env(cmdargs[k], temp);
	}
}

void	ft_export(char **cmdargs, t_shell *shell)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!cmdargs)
		return ;
	if (!cmdargs[1])
	{
		ft_export_no_args(*shell);
		return ;
	}
	i = ft_export_size_increase(cmdargs, shell, &j);
	temp = ft_copy_envp(shell->envp, i);
	if (!temp)
		return ;
	ft_add_env(cmdargs, temp, 0, shell);
	ft_free_envp(shell->envp);
	shell->envp = temp;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}
