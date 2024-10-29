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

static void	ft_multiple_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	ft_run_exec_node(t_token *token, t_shell *sh)
{
	t_iter	h;

	h.fd = 420;
	if (token->right)
	{
		if (sh->std_in == -1)
			sh->std_in = dup(STDIN_FILENO);
		if (sh->std_out == -1)
			sh->std_out = dup(STDOUT_FILENO);
		h.fd = ft_exec_redir(token->right, sh);
	}
	if (token->left && h.fd != -1)
	{
		if (!ft_isbuiltin(token->left->content))
			ft_execve(token->left, sh);
		else
			ft_exec_builtins_child(token, sh);
	}
	ft_restore_fd(sh->std_in, sh->std_out, sh);
}

void	ft_close_pipe(int exit[2], int pid[2], int pipe[2], t_shell *sh)
{
	ft_multiple_close(pipe[0], pipe[1]);
	waitpid(pid[0], &exit[0], 0);
	waitpid(pid[1], &exit[1], 0);
	sh->exit_status = WEXITSTATUS(exit[1]);
}

void	ft_run_this_pipe(int fd, int fd_pipe[2], t_token *token, t_shell *sh)
{
	ft_sig_restore();
	dup2(fd, STDOUT_FILENO);
	ft_multiple_close(fd_pipe[0], fd_pipe[1]);
	ft_run(token->left, sh);
}

void	ft_run_pipe(t_token *token, t_shell *sh)
{
	int		exit_status[2];
	int		pid_child[2];
	int		fd_pipe[2];

	if (pipe(fd_pipe) < 0)
		ft_printf(STDERR_FILENO, "Error in Pipe\n");
	ft_sig_mute();
	pid_child[0] = fork();
	if (pid_child[0] == 0)
		// ft_run_this_pipe(fd_pipe[2], fd_pipe, token->left, sh);
	{
		ft_sig_restore();
		dup2(fd_pipe[1], STDOUT_FILENO);
		ft_multiple_close(fd_pipe[0], fd_pipe[1]);
		ft_run(token->left, sh);
	}

	// teste com     export | greo
	if (token->left && token->left->left &&
		ft_isbuiltin(token->left->left->content) == TRUE
		&& ft_isbuiltin(token->right->left->content) == FALSE)
		wait(0);

	pid_child[1] = fork();
	if (pid_child[1] == 0)
		// ft_run_this_pipe(fd_pipe[0], fd_pipe, token->right, sh);
	{
		ft_sig_restore();
		dup2(fd_pipe[0], STDIN_FILENO);
		ft_multiple_close(fd_pipe[0], fd_pipe[1]);
		ft_run(token->right, sh);
	}
	ft_close_pipe(exit_status, pid_child, fd_pipe, sh);
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
