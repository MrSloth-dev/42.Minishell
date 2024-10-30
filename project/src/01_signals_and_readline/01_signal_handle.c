/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_signal_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:32:36 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/25 08:42:27 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_restore(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sig_mute(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	ft_get_exit_status(int exit_code, t_shell *sh)
{
	int	exit_status;

	if (WIFSIGNALED(exit_code))
	{
		exit_status = WTERMSIG(exit_code);
		if (exit_status == SIGINT)
			ft_printf(STDOUT_FILENO, "\n");
		else if (exit_status == SIGQUIT)
			ft_printf(STDOUT_FILENO, "Quit (core dumped)\n");
		if (WIFSIGNALED(exit_code))
			return (sh->exit_status = 128 + WTERMSIG(exit_code));
	}
	return (sh->exit_status = WEXITSTATUS(exit_code));
}
