/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:59:37 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 14:59:37 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_run_exec_node(t_token *token, t_shell *sh)
{
	t_iter	h;

	h.fd = 420;
	h.std_in = dup(STDIN_FILENO);
	h.std_out = dup(STDOUT_FILENO);
	if (token->right)
		h.fd = ft_exec_redir(token->right, sh);
	if (token->left && h.fd != -1)
	{
		if (!ft_isbuiltin(token->left->content))
			ft_execve(token->left, sh);
		else
			ft_exec_builtins_child(token, sh);
	}
	ft_restore_fd(h.std_in, h.std_out, sh);
}

void	ft_close_pipe(int exit[2], int pid[2], int pipe[2], t_shell *sh)
{
	close(pipe[0]);
	close(pipe[1]);
	waitpid(pid[0], &exit[0], 0);
	waitpid(pid[1], &exit[1], 0);
	sh->exit_status = WEXITSTATUS(exit[1]);
}

void	ft_run_pipe(t_token *token, t_shell *sh)
{
	int		exit_status[2];
	int		pid_child[2];
	int		pid_pipe[2];

	if (pipe(pid_pipe) < 0)
		ft_printf(STDERR_FILENO, "Error in Pipe\n");
	pid_child[0] = fork();
	if (pid_child[0] == 0)
	{
		dup2(pid_pipe[1], STDOUT_FILENO);
		close(pid_pipe[1]);
		close(pid_pipe[0]);
		ft_run(token->left, sh);
	}
	pid_child[1] = fork();
	if (pid_child[1] == 0)
	{
		dup2(pid_pipe[0], STDIN_FILENO);
		close(pid_pipe[1]);
		close(pid_pipe[0]);
		ft_run(token->right, sh);
	}
	ft_close_pipe(exit_status, pid_child, pid_pipe, sh);
}

void	ft_run(t_token *token, t_shell *sh)
{
	if (!token)
		ft_free_and_exit(NULL, sh, TRUE);
	if (token->type == ND_EXEC)
		ft_run_exec_node(token, sh);
	else if (token->type == ND_PIPE)
		ft_run_pipe(token, sh);
	ft_free_and_exit(NULL, sh, TRUE);
}
