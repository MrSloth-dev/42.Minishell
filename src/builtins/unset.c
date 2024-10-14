#include "minishell.h"

static void	ft_remove_env(char **temp, int j, t_shell *shell)
{
	int		k;

	k = 0;
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

void	ft_unset(t_token *cmdargs, t_shell *shell)
{
	char	**temp;
	t_token *head;
	int		i;
	int		j;

	head = cmdargs;
	i = 0;
	j = -1;
	if (!cmdargs->content)
		return ;
	while (cmdargs)
	{
		if (ft_env_exist(cmdargs->content, &j, shell->envp) != -1)
			i--;
		cmdargs = cmdargs->next;
	}
	cmdargs = head;
	while (cmdargs)
	{
		temp = ft_copy_envp(shell->envp, i);
		if (ft_env_exist(cmdargs->content, &j, shell->envp) != -1)
			ft_remove_env(temp, j, shell);
		cmdargs = cmdargs->next;
	}
	i = 0;
}
