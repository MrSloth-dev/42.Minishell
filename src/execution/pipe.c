#include "ft_printf.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_run_cmd(t_token *token, t_shell *shell)
{
	t_token	*cur_redir;
	int		exit_status[3];
	int		pid_child[3];
	int		pid_pipe[2];
	int		fd;

	if (!token)
		exit (10);
	if (token->type == ND_EXEC)
	{
		cur_redir = token->right;
		while (cur_redir)
		{
			if (cur_redir->type > HERE_DOC)
			{
				if (cur_redir->type == DBLE_REDIR_OUT)
					fd = open(cur_redir->content, O_RDWR | O_CREAT | O_APPEND, 0644);
				else
					fd = open(cur_redir->content, O_RDWR | O_CREAT, 0644);
				if (cur_redir->type == REDIR_IN)
					dup2(fd, STDIN_FILENO);
				else if (cur_redir->type >= REDIR_OUT)
					dup2(fd, STDOUT_FILENO);
			}
			cur_redir = cur_redir->next;
		}
		if (!ft_isbuiltin(token->left->content))
			ft_execve(token->left, shell);
		else
			ft_exec_builtins(token, shell);
	}
	else if (token->type == ND_PIPE)
	{
		if (pipe(pid_pipe) < 0)
			ft_printf(STDERR_FILENO, "Error in Pipe\n");
		pid_child[0] = fork();
		if (pid_child[0] == 0)
		{
			dup2(pid_pipe[1], STDOUT_FILENO);
			close(pid_pipe[0]);
			close(pid_pipe[1]);
			ft_run_cmd(token->left, shell);
		}
		pid_child[1] = fork();
		if (pid_child[1] == 0)
		{
			dup2(pid_pipe[0], STDIN_FILENO);
			close(pid_pipe[1]);
			close(pid_pipe[0]);
			ft_run_cmd(token->right, shell);
		}
		close(pid_pipe[0]);
		close(pid_pipe[1]);
		// wait(0);
		// wait(0);
		waitpid(pid_child[0], &exit_status[0], 0);
		waitpid(pid_child[1], &exit_status[1], 0);
		ft_free_and_exit(NULL, shell, TRUE);
	}
	ft_free_and_exit(NULL, shell, TRUE);
}
