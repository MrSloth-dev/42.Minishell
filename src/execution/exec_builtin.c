#include "minishell.h"
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

void	ft_exec_builtins(t_token *temp_head, t_shell *shell)
{
	t_token	*temp_next;

	temp_next = temp_head->next;
	if (temp_head && temp_head->next)
	{
		temp_next = temp_head->next;
		temp_next->prev = NULL;
	}
	if (ft_strcmp("cd", temp_head->content) == 0)
		ft_cd(temp_next, shell);
	else if (ft_strcmp("env", temp_head->content) == 0)
		ft_env(shell);
	else if (ft_strcmp("pwd", temp_head->content) == 0)
		ft_pwd(shell);
	else if (ft_strcmp("echo", temp_head->content) == 0)
		ft_echo(temp_next, shell);
	else if (ft_strcmp("export", temp_head->content) == 0)
		ft_export(temp_next, shell);
	else if (ft_strcmp("unset", temp_head->content) == 0)
		ft_unset(temp_next, shell);
	else if (ft_strcmp("exit", temp_head->content) == 0)
		ft_exit(NULL, shell);
}

void	ft_exec_builtins_child(t_token *cmdargs, t_shell *shell)
{
	t_token	*temp_head;

	temp_head = cmdargs;
	if (temp_head)
	{
		temp_head = temp_head->left;
		ft_exec_builtins(temp_head, shell);
	}
	ft_free_and_exit(NULL, shell, TRUE);
}

void	ft_exec_builtins_parent(t_token *cmdargs, t_shell *shell)
{
	int		fd;
	int		std_out;
	int		std_in;

	if (cmdargs->right)
	{
		std_out = dup(STDOUT_FILENO);
		std_in = dup(STDIN_FILENO);
	}
	fd = ft_exec_redir(cmdargs->right);
	ft_exec_builtins(cmdargs->left, shell);
	if (fd != -1)
	{
		dup2(std_out, STDOUT_FILENO);
		dup2(std_in, STDIN_FILENO);
		close(std_in);
		close(std_out);
		close(fd);
	}
}

int	ft_exec_redir(t_token *cur_redir)
{
	int		fd;

	fd = -1;
	while (cur_redir)
	{
		if (cur_redir->type > HERE_DOC)
		{
			if (cur_redir->type == DBLE_REDIR_OUT)
				fd = open(cur_redir->content, O_RDWR
						| O_CREAT | O_APPEND, 0644);
			else if (cur_redir->type == REDIR_OUT)
				fd = open(cur_redir->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (cur_redir->type == REDIR_IN)
				fd = open(cur_redir->content, O_RDONLY, 0644);
			if (cur_redir->type == REDIR_IN)
				dup2(fd, STDIN_FILENO);
			else if (cur_redir->type >= REDIR_OUT)
				dup2(fd, STDOUT_FILENO);
		}
		cur_redir = cur_redir->next;
	}
	return (fd);
}
