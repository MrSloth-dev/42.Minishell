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

static void	ft_run_exec_node(t_token *token, t_shell *sh)
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
	if (token->right)
		ft_restore_fd(sh->std_in, sh->std_out, sh);
}

static void	ft_this_pipe(int FLAG, int fd_pipe[2], t_token *token, t_shell *sh)
{
	ft_sig_restore();
	if (FLAG == 1)
		dup2(fd_pipe[1], STDOUT_FILENO);
	else
		dup2(fd_pipe[0], STDIN_FILENO);
	ft_multiple_close(fd_pipe[0], fd_pipe[1]);
	ft_run(token, sh);
}

static void	ft_run_pipes(t_token *token, t_shell *sh)
{
	int		exit_status[2];
	int		pid_child[2];
	int		fd_pipe[2];

	exit_status[0] = 0;
	exit_status[1] = 0;
	if (pipe(fd_pipe) < 0)
		ft_printf(STDERR_FILENO, "Error in Pipe\n");
	ft_sig_mute();
	pid_child[0] = fork();
	if (pid_child[0] == 0)
		ft_this_pipe(1, fd_pipe, token->left, sh);
	if (token->left && token->left->left
		&& ft_isbuiltin(token->left->left->content) == TRUE
		&& token->right && token->right->left
		&& ft_isbuiltin(token->right->left->content) == FALSE)
		wait(0);
	pid_child[1] = fork();
	if (pid_child[1] == 0)
		ft_this_pipe(0, fd_pipe, token->right, sh);
	ft_close_pipe(exit_status, pid_child, fd_pipe, sh);
}

void	ft_run(t_token *token, t_shell *sh)
{
	if (!token)
		ft_free_and_exit(NULL, sh, TRUE);
	if (token->type == ND_EXEC)
		ft_run_exec_node(token, sh);
	else if (token->type == ND_PIPE)
		ft_run_pipes(token, sh);
	ft_free_and_exit(NULL, sh, TRUE);
}
