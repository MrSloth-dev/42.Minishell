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

void	ft_close_pipe(int exit[2], int pid[2], int pipe[2], t_shell *sh)
{
	ft_multiple_close(pipe[0], pipe[1]);
	waitpid(pid[0], &exit[0], 0);
	waitpid(pid[1], &exit[1], 0);
	sh->exit_status = WEXITSTATUS(exit[1]);
}
