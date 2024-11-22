/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_run_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:47:32 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/29 11:48:08 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_multiple_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

int	ft_get_exit_signal(int *exit, t_shell *sh)
{
	int	exit_status[2];

	if (WIFSIGNALED(exit[0]) || WIFSIGNALED(exit[1]))
	{
		exit_status[0] = WTERMSIG(exit[0]);
		exit_status[1] = WTERMSIG(exit[1]);
		if (exit_status[0] == SIGINT && exit_status[1] == SIGINT)
			ft_printf(STDOUT_FILENO, "\n");
		else if (exit_status[0] == SIGQUIT && exit_status[1] == SIGQUIT)
			ft_printf(STDOUT_FILENO, "Quit (core dumped)\n");
		if (WIFSIGNALED(exit[1]))
			return (sh->exit_status = 128 + WTERMSIG(exit[1]));
	}
	return (sh->exit_status = WEXITSTATUS(exit[1]));
}

void	ft_close_pipe(int exit[2], int pid[2], int pipe[2], t_shell *sh)
{
	ft_multiple_close(pipe[0], pipe[1]);
	waitpid(pid[0], &exit[0], 0);
	waitpid(pid[1], &exit[1], 0);
	sh->exit_status = ft_get_exit_signal(exit, sh);
}
