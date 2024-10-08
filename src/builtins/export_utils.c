#include "minishell.h"
#include <unistd.h>

void	ft_swap_plus_env(char *cmdargs, char **temp, int j, t_shell *shell)
{
	int		k;
	char *joinvalue;

	joinvalue = ft_get_env_value(cmdargs, temp, shell);
	k = 0;
	while (temp[k])
	{
		if (j == k)
			temp[k] = ft_strjoin_free(temp[k], joinvalue);
		if (!temp[k])
			return ;
		k++;
	}
}

void	ft_swap_env(char *cmdargs, char **temp, int j)
{
	int		k;

	k = 0;
	while (temp[k])
	{
		if (j == k)
			temp[k] = ft_strdup(cmdargs);
		if (!temp[k] || j == k)
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
	// temp[i] = 0;
}

char	**ft_order_env(char **env)
{
	char	**order;
	char	*swap;
	int		size;
	int		i;

	i = 0;
	size = 0;
	order = ft_copy_envp(env, 0);
	while (order[size])
		size++;
	while (i < size - 1)
	{
		if (ft_strcmp(order[i], order[i + 1]) > 0)
		{
			swap = order[i];
			order[i] = order[i + 1];
			order[i + 1] = swap;
			i = 1;
		}
		else
			i++;
	}
	return (order);
}

void	ft_export_no_args(t_shell shell)
{
	int		i;
	char	**order;
	char	*value;

	order = ft_order_env(shell.envp);
	i = 0;
	i = 0;
	while (order[i])
	{
		ft_printf(STDOUT_FILENO, "declare -x %s=", ft_get_env_key(order[i]));
		value = ft_get_env_value(order[i], order, &shell);
		if (!value)
			ft_printf(STDOUT_FILENO, "\"\"\n");
		else
			ft_printf(STDOUT_FILENO, "\"%s\"\n", value);
		i++;
	}
	i = 0;
	while (order[i])
		free(order[i++]);
	free(order);
}
