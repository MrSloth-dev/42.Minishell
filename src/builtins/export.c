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

static int	ft_export_duplicate(t_token *cmdargs, int k)
{
	char	*temp;

	temp = cmdargs->content;
	while (--k)
	{
		if (cmdargs->content == temp)
			return (1);
		cmdargs = cmdargs->prev;
	}
	return (0);
}

static int	ft_export_size_increase(t_token *cmdargs, t_shell *shell, int *j)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	*j = -1;
	while (shell->envp[i])
		i++;
	while (cmdargs)
	{
		if (ft_env_exist(cmdargs->content, j, shell->envp) == -1
			&& !ft_strchr(cmdargs->content, '='))
			i++;
		if (ft_export_duplicate(cmdargs, k))
			i--;
		k++;
		cmdargs = cmdargs->next;
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

void	ft_add_env(t_token *cmdargs, char **temp, int plus_mode, t_shell *shell)
{
	int	j;

	j = -1;
	while (cmdargs->content && cmdargs->next)
	{
		cmdargs = cmdargs->next;
		if (!ft_strchr(cmdargs->content, '='))
			continue ;
		plus_mode = ft_plus_mode(cmdargs->content);
		if (ft_env_exist(cmdargs->content, &j, temp) != -1 && plus_mode)
			ft_swap_plus_env(cmdargs->content, temp, j, shell);
		else if (ft_env_exist(cmdargs->content, &j, temp) != -1 && !plus_mode)
			ft_swap_env(cmdargs->content, temp, j);
		else
			ft_append_env(cmdargs->content, temp);
	}
}

void	ft_export(t_token *cmdargs, t_shell *shell)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!cmdargs)
		return ;
	if (!cmdargs->next)
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
	i = -1;
}
