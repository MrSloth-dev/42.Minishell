#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_check_file_access(char *file, int redir, t_shell *sh)
{
	struct stat	stat_path;

	if (stat(file, &stat_path) == -1 && (redir != REDIR_OUT || redir != DBLE_REDIR_OUT))
		return (ft_printf(STDERR_FILENO, "%s: %s: No such file or directory\n",
				sh->prog_name, file), 0);
	if (redir == REDIR_IN || redir == HERE_DOC)
		if (access(file, R_OK) == -1)
			return (ft_printf(STDERR_FILENO, "%s: %s: Permission denied\n",
					sh->prog_name, file), 0);
	if (redir == REDIR_OUT)
		if (stat(file, &stat_path) != -1 && access(file, W_OK) == -1)
			return (ft_printf(STDERR_FILENO, "%s: %s: Permission denied\n",
					sh->prog_name, file), 0);
	return (1);
}

void	ft_run_cmd(t_token *token, t_shell *sh)
{
	int		exit_status[3];
	int		pid_child[3];
	int		pid_pipe[2];
	int		fd;

	fd = 420;
	if (!token)
		exit (10);
	if (token->type == ND_EXEC)
	{
		if (token->right)
			fd = ft_exec_redir(token->right, sh);
		if (fd != -1)
		{
			if (token->left && !ft_isbuiltin(token->left->content))
				ft_execve(token->left, sh);
			else
				ft_exec_builtins_child(token, sh);
		}
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
