#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_run_cmd(t_token *token, t_shell *sh)
{
	int		exit_status[3];
	int		pid_child[3];
	int		pid_pipe[2];
	t_iter	helper;

	helper.fd = 420;
	if (!token)
		ft_free_and_exit(NULL, sh, TRUE);
	if (token->type == ND_EXEC)
	{
	int		stdin = dup(STDIN_FILENO);
	int		stdout = dup(STDOUT_FILENO);
		if (token->right)
			fd = ft_exec_redir(token->right, sh);
		if (token->left && fd != -1)
		{
			if (!ft_isbuiltin(token->left->content))
				ft_execve(token->left, sh);
			else
				ft_exec_builtins_child(token, sh);
		}
		ft_restore_fd(stdin, stdout, sh);
	}
	else if (token->type == ND_PIPE)
	{
		if (pipe(pid_pipe) < 0)
			ft_printf(STDERR_FILENO, "Error in Pipe\n");
		pid_child[0] = fork();
		if (pid_child[0] == 0)
		{
			dup2(pid_pipe[1], STDOUT_FILENO);
			close(pid_pipe[1]);
			close(pid_pipe[0]);
			ft_run_cmd(token->left, sh);
		}
		pid_child[1] = fork();
		if (pid_child[1] == 0)
		{
			dup2(pid_pipe[0], STDIN_FILENO);
			close(pid_pipe[1]);
			close(pid_pipe[0]);
			ft_run_cmd(token->right, sh);
		}
		close(pid_pipe[0]);
		close(pid_pipe[1]);
		
		waitpid(pid_child[0], &exit_status[0], 0);
		waitpid(pid_child[1], &exit_status[1], 0);
		sh->exit_status = WEXITSTATUS(exit_status[1]);
	}
	ft_free_and_exit(NULL, sh, TRUE);
}
