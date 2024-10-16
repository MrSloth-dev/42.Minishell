#include "ft_printf.h"
#include "minishell.h"
#include <cstdio>

/* int	ft_pipex(t_token *token, t_shell *shell)
{
	int	i;
	int	temp_fd;
	char	**cmd;

	temp_fd = pipex->infile;
	i = 0;
	while (i < pipex->cmd_count)
	{
		cmd = ft_get_and_check_cmd(pipex->argv[i + pipex->offset_args], pipex);
		if (access(cmd[0], X_OK) == 0)
			ft_execute_command(&temp_fd, cmd, pipex, i);
		else
			command_not_found(cmd[0], cmd, pipex);
		free_splited_mat(cmd);
		
	}
	return (SUCCESS);
}
*/
char **ft_create_cmdargs(t_token *token)
{
	char	**cmdargs;
	t_token	*head;
	int		len;

	head = token;
	len = 0;
	while (token && token->next != NULL)
	{
		len++;
		token = token->next;
	}
	token = head;
	cmdargs = malloc(sizeof(char *) * len);
	len = 0;
	while (token && token->next != NULL)
	{
		cmdargs[len] = ft_strdup(token->content);
		token = token->next;
	}
	cmdargs[len] = 0;
	return (cmdargs);
}

/*
void	ft_execute_command(t_token *cmd, t_shell *shell)
{
	pid_t	pid;
	int		fd[2];
	char	**cmdargs;

	cmdargs = ft_create_cmdargs(cmd);
	pipe(fd);
	pid = fork();
	// if (pid == -1)
	// 	ft_error_msg("Error with Fork ", FORK_ERROR);
	if (pid == 0)
	{
		// dup2(temp_fd[0], STDIN_FILENO);
		// if (index == 1)
		// 	ft_dup2(pipex->outfile, STDOUT_FILENO);
		// else
		// 	ft_dup2(fd[1], STDOUT_FILENO);
		// close(fd[0]);
		execve(cmdargs[0], cmdargs, shell->envp);
	}
	waitpid(-1, &shell->exit_status, WNOHANG);
	close(fd[0]);
	close(fd[1]);
}
*/
