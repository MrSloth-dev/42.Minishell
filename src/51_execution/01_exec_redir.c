#include "minishell.h"

int	ft_exec_redir(t_token *cur_redir, t_shell *sh)
{
	int		fd;

	fd = 420;
	while (cur_redir)
	{
		if (cur_redir->type >= HERE_DOC)
		{
			if (cur_redir->type == DBLE_REDIR_OUT)
				fd = open(cur_redir->content, O_RDWR
						| O_CREAT | O_APPEND, 0644);
			else if (cur_redir->type == REDIR_OUT)
				fd = open(cur_redir->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (cur_redir->type == REDIR_IN)
				fd = open(cur_redir->content, O_RDONLY, 0644);
			else if (cur_redir->type == HERE_DOC)
				fd = open(cur_redir->file, O_RDONLY, 0644);
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
	if (cur_redir)
	{
		if ((cur_redir->type == HERE_DOC && !ft_check_file_access(cur_redir->file, cur_redir->type, sh)))
			fd = -1;
		else if (!ft_check_file_access(cur_redir->content, cur_redir->type, sh))
			fd = -1;
	}
	if (fd == -1)
		sh->exit_status = 1;
	else
		sh->exit_status = 0;
	return (fd);
}

void	ft_restore_fd(int std_in, int std_out, t_shell *sh)
{
	(void)sh->exit_status;
	dup2(std_out, STDOUT_FILENO);
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	close(std_out);
}

