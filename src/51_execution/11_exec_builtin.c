/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:05:40 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:05:40 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtins(t_token *temp_head, t_shell *shell)
{
	t_token	*temp_next;

	temp_next = NULL;
	if (temp_head && temp_head->next)
	{
		temp_next = temp_head->next;
		temp_next->prev = NULL;
	}
	if (ft_strcmp(temp_head->content, "cd") == 0)
		ft_cd(temp_next, shell);
	else if (ft_strcmp(temp_head->content, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(temp_head->content, "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(temp_head->content, "echo") == 0)
		ft_echo(temp_next, shell);
	else if (ft_strcmp(temp_head->content, "export") == 0)
		ft_export(temp_next, shell);
	else if (ft_strcmp(temp_head->content, "unset") == 0)
		ft_unset(temp_next, shell);
	else if (ft_strcmp(temp_head->content, "exit") == 0)
		ft_exit(temp_next, shell);
}

void	ft_exec_builtins_child(t_token *cmdargs, t_shell *sh)
{
	if (cmdargs)
		ft_exec_builtins(cmdargs->left, sh);
}

void	ft_exec_builtins_parent(t_token *cmdargs, t_shell *sh)
{
	int		fd;
	int		std_out;
	int		std_in;

	fd = 420;
	if (cmdargs->right)
	{
		std_out = dup(STDOUT_FILENO);
		std_in = dup(STDIN_FILENO);
		fd = ft_exec_redir(cmdargs->right, sh);
	}
	if (fd != -1)
		ft_exec_builtins(cmdargs->left, sh);
	if (cmdargs->right)
		ft_restore_fd(std_in, std_out, sh);
}
