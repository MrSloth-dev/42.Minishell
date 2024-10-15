#include "minishell.h"
#include <unistd.h>

void	ft_run_cmd(t_token *token, t_shell *shell)
{
	int	pid_pipe[2];
	int	pid_child[2];
	int	exit_status[2];
	if (!token)
		exit (10);
	if (token->type == ND_EXEC)
	{
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
			ft_run_cmd(token->left, shell);
		}
		pid_child[1] = fork();
		if (pid_child[1] == 0)
		{
			dup2(pid_pipe[0], STDIN_FILENO);
			close(pid_pipe[1]);
			ft_run_cmd(token->right, shell);
		}
		close(pid_pipe[0]);
		close(pid_pipe[1]);
		waitpid(pid_child[0], &exit_status[0], 0);
		waitpid(pid_child[1], &exit_status[1], 0);
	}
	else
		exit (10);
}
