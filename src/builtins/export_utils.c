#include "minishell.h"

void	ft_swap_env(char *cmdargs, char **temp, int j)
{
	int		k;

	k = 0;
	j--;
	while (temp[k])
	{
		if (j == k)
			temp[k] = ft_strdup(cmdargs);
		if (!temp[k])
			return ;
		k++;
	}
}

void	ft_append_env(char *cmdargs, char **temp)
{
	int		i;

	i = 0;
	while (temp[i])
		i++;
	temp[i++] = ft_strdup(cmdargs);
	temp[i] = 0;
}

void	ft_export_no_args(t_shell shell)
{
	int		i;
	int		size;
	char	*swap;

	i = 0;
	size = 0;
	while (shell.envp[size])
		size++;
	while (i < size - 1)
	{
		if (ft_strcmp(shell.envp[i], shell.envp[i + 1]) > 0)
		{
			swap = shell.envp[i];
			shell.envp[i] = shell.envp[i + 1];
			shell.envp[i + 1] = swap;
			i = 1;
		}
		else
			i++;
	}
	i = 0;
	while (shell.envp[i])
	{
		ft_printf(1, "declare -x %s=", ft_get_env_key(shell.envp[i]));
		ft_printf(1, "\"%s\"\n", ft_get_env_value(shell.envp[i], &shell));
		i++;
	}
}
