/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:59:43 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 14:59:43 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_exit_redir(t_token *cur_redir, t_shell *sh, int *fd)
{
	if (cur_redir)
	{
		if ((cur_redir->type == HERE_DOC
				&& !ft_check_file_access(cur_redir->file, cur_redir->type, sh)))
			*fd = -1;
		else if (!ft_check_file_access(cur_redir->content, cur_redir->type, sh))
			*fd = -1;
	}
	if (*fd == -1)
		sh->exit_status = 1;
	else
		sh->exit_status = 0;
}

static void	ft_assert_redir(t_token *cur_redir, int *fd)
{
	if (cur_redir->type == DBLE_REDIR_OUT)
		*fd = open(cur_redir->content, O_RDWR
				| O_CREAT | O_APPEND, 0644);
	else if (cur_redir->type == REDIR_OUT)
		*fd = open(cur_redir->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (cur_redir->type == REDIR_IN)
		*fd = open(cur_redir->content, O_RDONLY, 0644);
	else if (cur_redir->type == HERE_DOC)
		*fd = open(cur_redir->file, O_RDONLY, 0644);
}

int	ft_exec_redir(t_token *cur_redir, t_shell *sh)
{
	int		fd;

	fd = 420;
	while (cur_redir)
	{
		if (cur_redir->type >= HERE_DOC)
		{
			ft_assert_redir(cur_redir, &fd);
			if (fd == -1)
				break ;
			if (cur_redir->type == REDIR_IN || cur_redir->type == HERE_DOC)
				dup2(fd, STDIN_FILENO);
			else if (cur_redir->type >= REDIR_OUT)
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		cur_redir = cur_redir->next;
	}
	ft_handle_exit_redir(cur_redir, sh, &fd);
	return (fd);
}

void	ft_restore_fd(int std_in, int std_out, t_shell *sh)
{
	char	buffer[1];

	(void)sh->exit_status;
	if (read(std_in, buffer, 0) != -1)
	{
		dup2(std_in, STDIN_FILENO);
		close(std_in);
	}
	if (read(std_out, buffer, 0) != -1)
	{
		dup2(std_out, STDOUT_FILENO);
		close(std_out);
	}
}
