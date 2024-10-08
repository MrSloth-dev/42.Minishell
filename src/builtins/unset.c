#include "minishell.h"

static void	ft_remove_env(char **temp, int j, t_shell *shell)
{
	int		k;

	k = 0;
	j--;
	while (shell->envp[k])
	{
		if (j == k)
			k++;
		else
			temp[k] = ft_strdup(shell->envp[k]);
		if (!temp[k])
			return ;
		k++;
	}
}

char	**ft_unset(char **cmdargs, t_shell *shell)
{
	char	**temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 1;
	j = -1;
	if (cmdargs == NULL)
		return (NULL);
	while (cmdargs[k])
		if (ft_env_exist(cmdargs[k++], &j, shell->envp) == -1)
			i--;
	k = 0;
	while (cmdargs[++k])
	{
		temp = ft_copy_envp(shell->envp, i);
		ft_env_exist(cmdargs[k], &j, shell->envp);
		i = 0;
		if (j != -1)
			ft_remove_env(temp, j, shell);
	}
	while (temp[i])
		printf("%s\n", temp[i++]);
	return (temp);
}
