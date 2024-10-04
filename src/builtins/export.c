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

void	ft_copy_env(char **temp, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		temp[i] = ft_strdup(env[i]);
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
		if (ft_env_exist(cmdargs[k++], j, shell->envp) == -1)
			i++;
		if (ft_export_duplicate(cmdargs, k))
			i--;
	}
	return (i);
}

char	**ft_export(char **cmdargs, t_shell *shell)
{
	char	**temp;
	int		i;
	int		j;
	int		k;
	int		plus_mode;

	i = 0;
	if (!cmdargs)
		return (NULL);
	if (!cmdargs[1])
		ft_export_no_args(*shell);
	plus_mode = 0;
	i = ft_export_size_increase(cmdargs, shell, &j);
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	ft_copy_env(temp, shell->envp);
	k = 0;
	while (cmdargs[++k])
	{
		j = -1;
		if ((ft_strchr(cmdargs[k], '=') - ft_strchr(cmdargs[k], '+')) == 1)
			plus_mode = 1;
		if (ft_env_exist(cmdargs[k], &j, temp) != -1 && plus_mode)
			ft_swap_env(cmdargs[k], temp, j);
		else if (ft_env_exist(cmdargs[k], &j, temp) != -1 && !plus_mode)
			ft_swap_env(cmdargs[k], temp, j);
		else
			ft_append_env(cmdargs[k], temp);
	}
	return (temp); // Need to free the original struct I think
}
