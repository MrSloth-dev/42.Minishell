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
	ft_free_and_exit(NULL, sh, TRUE);
}

void	ft_restore_fd(int std_in, int std_out, t_shell *sh)
{
	sh->exit_status = 1;
	dup2(std_out, STDOUT_FILENO);
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	close(std_out);
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
	{
		ft_exec_builtins(cmdargs->left, sh);
		if (cmdargs->right)
			ft_restore_fd(std_in, std_out, sh);
		// close(fd);
	}
	if (cmdargs->right)
	{
		close(std_in);
		close(std_out);
	}
}

int	ft_exec_redir(t_token *cur_redir, t_shell *sh)
{
	int		fd;

	fd = -1;
	while (cur_redir)
	{
		if (cur_redir->type >= HERE_DOC)
		{
			if ((cur_redir->type == HERE_DOC && !ft_check_file_access(cur_redir->file, cur_redir->type, sh)) && !ft_check_file_access(cur_redir->content, cur_redir->type, sh))
				return (-1);
			// if (!ft_check_file_access(cur_redir->content, cur_redir->type, sh))
			// 	return (-1);
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
				return (-1);
			if (cur_redir->type == REDIR_IN || cur_redir->type == HERE_DOC)
				dup2(fd, STDIN_FILENO);
			else if (cur_redir->type >= REDIR_OUT)
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		cur_redir = cur_redir->next;
	}
	if (fd == -1)
		sh->exit_status = 1;
	return (fd);
}
