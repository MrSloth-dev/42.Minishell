/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:04:37 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/25 10:12:03 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc(char delimiter[4096], char file[4096])
{
	int		fd;
	char	*line;

	while (1)
	{
		line = readline("> ");
		fd = open(file, O_RDWR | O_APPEND, 0644);
		if (line == NULL)
		{
			ft_printf(1, "minishell: warning: here-document delimited ");
			ft_printf(1, "by end-of-file (wanted `%s')\n", delimiter);
			return (ft_free(line), close(fd), 0);
		}
		else if (ft_strcmp(line, delimiter) == 0)
			return (ft_free(line), close(fd), 0);
		else if ((line || *(line)))
		{
			ft_printf(fd, "%s", line);
			write(fd, "\n", 1);
			close(fd);
		}
		line = ft_free(line);
	}
}

static int	ft_do_this_hd(t_shell *sh, char delimiter[4096], char file[4096])
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		ft_sig_child();
		ft_free_inside_heredoc(sh);
		ft_here_doc(delimiter, file);
		exit (0);
	}
	else
	{
		ft_sig_mute();
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			ft_printf(STDOUT_FILENO, "\n");
			sh->head = NULL;
			sh->exit_status = 128 + WTERMSIG(status);
			return (ft_sig_restore(), 1);
		}
	}
	return (0);
}

static int	ft_are_file_paths_and_delimiters_too_long(t_token *cur)
{
	while (cur)
	{
		if (cur->file && ft_strlen(cur->file) > 4001)
		{
			ft_printf(1,
				"Please, do not try run program inside a big file paths.\n");
			return (TRUE);
		}
		if (cur->content && ft_strlen(cur->content) > 4001)
		{
			ft_printf(1,
				"\nSerious, you're trying more than 4000 char's\
 as a delimiter?!?!\n");
			return (TRUE);
		}
		cur = cur->front;
	}
	return (FALSE);
}

int	ft_run_heredocs(t_token *token, t_shell *sh)
{
	t_token	*cur;
	char	hd_file[4096];
	char	delimiter[4096];
	int		hd_continue;

	hd_continue = -1;
	if (!token || !sh || sh->nb_heredoc < 1)
		return (1);
	cur = token;
	if (ft_are_file_paths_and_delimiters_too_long(cur) == TRUE)
		return (ft_sig_restore(), 0);
	while (cur)
	{
		if (cur->file)
		{
			ft_get_file_name(hd_file, cur->file);
			ft_get_delimiter(delimiter, cur->content);
			hd_continue = ft_do_this_hd(sh, delimiter, hd_file);
		}
		if (hd_continue == 1)
			break ;
		cur = cur->front;
	}
	return (ft_sig_restore(), 0);
}
