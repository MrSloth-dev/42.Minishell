/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:05:56 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:09:02 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_bin_error(char *bin, t_shell *shell)
{
	struct stat	path_stat;

	if (stat(bin, &path_stat) == -1)
		return (shell->exit_status = 127, 127);
	else if (S_ISDIR(path_stat.st_mode))
		return (shell->exit_status = 126, 128);
	else if (S_ISREG(path_stat.st_mode) && access(bin, X_OK) == -1)
		return (shell->exit_status = 126, 126);
	else if (access(bin, R_OK) == -1)
		return (shell->exit_status = 127, 127);
	return (0);
}

static char	*ft_get_cmdbin(t_token *token, t_shell *shell)
{
	char	*temp;
	char	*path;
	int		i;
	int		err;

	i = 0;
	temp = NULL;
	path = ft_get_env_value("PATH", shell->envp, shell);
	shell->path = ft_split(path, ':');
	if (!shell->path || !*shell->path)
		return (NULL);
	while (shell->path[i])
	{
		temp = ft_strjoin(shell->path[i], "/");
		temp = ft_strjoin_free(temp, ft_strdup(token->content));
		err = access(temp, X_OK);
		if (err == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

static char	**ft_create_cmdargs(t_token *token)
{
	char	**cmdargs;
	t_token	*head;
	int		len;

	head = token;
	len = 0;
	while (head && head->content != NULL)
	{
		len++;
		head = head->next;
	}
	head = token;
	cmdargs = ft_calloc(len + 1, sizeof(char *));
	if (!cmdargs)
		return (NULL);
	len = 0;
	while (head && head->content != NULL)
	{
		cmdargs[len] = ft_strdup(head->content);
		head = head->next;
		len++;
	}
	return (cmdargs);
}

void	ft_execve(t_token *cmd, t_shell *shell)
{
	char	**cmdargs;
	char	*cmdbin;
	int		error;

	error = 0;
	if (!cmd->content)
		return ;
	cmdargs = ft_create_cmdargs(cmd);
	cmdbin = ft_get_cmdbin(cmd, shell);
	error = ft_check_bin_error(cmdbin, shell);
	if (!error && (cmd->content[0] != '.' && cmd->content[1] != '/'))
		error = execve(cmdbin, cmdargs, shell->envp);
	else
	{
		error = ft_check_bin_error(cmd->content, shell);
		if (!error)
			execve(cmd->content, cmdargs, shell->envp);
	}
	ft_print_execve_error(error, cmd, shell);
	ft_free_envp(cmdargs);
	ft_free(cmdbin);
}
