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

