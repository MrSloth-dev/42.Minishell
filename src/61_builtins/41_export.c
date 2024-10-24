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

int	ft_env_duplicate(t_token *cmdargs)
{
	char	*temp;

	temp = cmdargs->content;
	cmdargs = cmdargs->prev;
	while (cmdargs)
	{
		if (ft_strcmp(cmdargs->content, temp) == 0)
			return (ft_printf(1, "dup"));
		cmdargs = cmdargs->prev;
	}
	return (0);
}

static int	ft_export_size_increase(t_token *cmdargs, t_shell *shell, int *j)
{
	t_token	*current;
	int		i;

	i = 0;
	*j = -1;
	current = cmdargs;
	while (shell->envp[i])
		i++;
	while (current)
	{
		if (ft_env_exist(current->content, j, shell->envp) == -1)
			i++;
		if (ft_env_duplicate(current))
			i--;
		current = current->next;
	}
	return (i);
}

int	ft_plus_mode(char *cmdargs)
{
	int	i;

	if (!ft_strchr(cmdargs, '='))
		return (0);
	i = 0;
	while (cmdargs[i] && cmdargs[i] != '=')
		if (cmdargs[i++] == '+')
			return (1);
	return (0);
}

int	ft_valid_identifiers(t_token *cmdargs, t_shell *sh)
{
	int	i;

	if (!cmdargs || !cmdargs->content)
		return (0);
	if (ft_strchr("=+", cmdargs->content[0]))
		return (ft_printf(STDERR_FILENO,
				"%s : export : `%s': not a valid identifier\n",
				sh->prog_name, cmdargs->content), 0);
	if (!ft_isalpha(cmdargs->content[0]) && cmdargs->content[0] != '_')
		return (ft_printf(STDERR_FILENO,
				"%s : export : `%s': not a valid identifier\n",
				sh->prog_name, cmdargs->content), 0);
	i = 1;
	if (!ft_strchr(cmdargs->content, '=') && ft_strchr(cmdargs->content, '+'))
		return (ft_printf(STDERR_FILENO,
				"%s : export : `%s': not a valid identifier\n",
				sh->prog_name, cmdargs->content), 0);
	while (cmdargs->content[i] && !ft_strchr("=+", cmdargs->content[i]))
	{
		if (ft_isalnum(cmdargs->content[i]) || cmdargs->content[i] == '_')
			i++;
		else
			return (ft_printf(STDERR_FILENO,
					"%s : export : `%s': not a valid identifier\n",
					sh->prog_name, cmdargs->content), 0);
	}
	return (1);
}

void	ft_add_env(t_token *cmdargs, char **temp, int plus_mode, t_shell *shell)
{
	t_token	*current;
	int		j;

	current = cmdargs;
	j = -1;
	while (current && current->content)
	{
		if (!ft_valid_identifiers(cmdargs, shell))
		{
			current = current->next;
			shell->exit_status = EXIT_FAILURE;
			continue ;
		}
		plus_mode = ft_plus_mode(current->content);
		if (ft_env_exist(current->content, &j, temp) != -1 && plus_mode)
			ft_swap_plus_env(current->content, temp, j, shell);
		else if (ft_env_exist(current->content, &j, temp) != -1 && !plus_mode)
			ft_swap_env(current->content, temp, j);
		else
			ft_append_env(current->content, temp);
		current = current->next;
		shell->exit_status = EXIT_SUCCESS;
	}
}

void	ft_export(t_token *cmdargs, t_shell *shell)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	shell->exit_status = EXIT_SUCCESS;
	if (!cmdargs)
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
}
