#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

char	*ft_get_cmd(t_token *token, t_shell *shell)
{
	char	*temp;
	int		i;
	int		err;

	i = 0;
	temp = NULL;
	while (shell->path[i])
	{
		temp = ft_strjoin(shell->path[i], "/");
		temp = ft_strjoin_free(temp, ft_strdup(token->content));
		err = access(temp, X_OK);
		if (err == 0)
			return (temp);
		free(temp);
		i++;
	}
	// ft_error_msg("Command not found", 127);
	return (NULL);
}

char	**ft_create_cmdargs(t_token *token)
{
	char	**cmdargs;
	t_token	*head;
	int		len;

	head = token;
	len = 0;
	while (token && token->content != NULL)
	{
		len++;
		if (token->next != NULL)
			token = token->next;
		else
			break ;
	}
	token = head;
	cmdargs = malloc(sizeof(char *) * len);
	if (!cmdargs)
		return (NULL);
	len = 0;
	while (token && token->content != NULL)
	{
		cmdargs[len++] = ft_strdup(token->content);
		token = token->next;
	}
	return (cmdargs);
}

void	ft_execute_command(t_token *cmd, t_shell *shell)
{
	pid_t	pid;
	int		fd[2];
	char	**cmdargs;
	char	*cmdbin;

	cmdargs = ft_create_cmdargs(cmd);
	cmdbin = ft_get_cmd(cmd, shell);
	pipe(fd);
	pid = fork();
	if (pid == -1)
		ft_printf(STDERR_FILENO, "Error in pipe");
	if (pid == 0)
	{
		// dup2(temp_fd[0], STDIN_FILENO);
		// if (index == 1)
		// 	ft_dup2(pipex->outfile, STDOUT_FILENO);
		// else
		// 	ft_dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execve(cmdbin, cmdargs, shell->envp);
		exit(0);
	}
	waitpid(pid, &shell->exit_status, 0);
	int i = 0;
	while (cmdargs[i++])
		free(cmdargs[i]);
	free(cmdargs);
	free(cmdbin);
	close(fd[0]);
	close(fd[1]);
}

