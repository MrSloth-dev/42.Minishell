#include "ft_printf.h"
#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

char	*ft_get_cmdbin(t_token *token, t_shell *shell)
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
	return (NULL);
}

int	ft_check_bin(char *bin, t_token *token, t_shell *shell)
{
	struct stat	path_stat;

	stat(bin, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf(STDERR_FILENO, "%s : Is a directory\n", token->content);
		return (shell->exit_status = 126, 0);
	}
	else if (access(bin, X_OK) == -1)
	{
		ft_printf(STDERR_FILENO, "%s : command not found\n", token->content);
		return (shell->exit_status = 127, 0);
	}
	return (1);
}

char	**ft_create_cmdargs(t_token *token)
{
	char	**cmdargs;
	t_token	*head;
	int		len;

	head = token;
	len = 0;
	while (head && head->content != NULL)
	{
		len++;
		head = head->next;
	}
	head = token;
	cmdargs = ft_calloc(len + 1, sizeof(char *));
	if (!cmdargs)
		return (NULL);
	len = 0;
	while (head && head->content != NULL)
	{
		cmdargs[len] = ft_strdup(head->content);
		head = head->next;
		len++;
	}
	return (cmdargs);
}

void	ft_execve(t_token *cmd, t_shell *shell)
{
	char	**cmdargs;
	char	*cmdbin;

	if (!cmd->content)
		return ;
	cmdargs = ft_create_cmdargs(cmd);
	cmdbin = ft_get_cmdbin(cmd, shell);
	if (ft_check_bin(cmdbin, cmd, shell))
	{
		execve(cmdbin, cmdargs, shell->envp);
	}
	ft_free_envp(cmdargs);
	ft_free(cmdbin);
	ft_free_and_exit(NULL, shell, TRUE);
}

/* ISILVA COMMENTED THIS FOR TESTING! SEE ABOVE NEW FT
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
	cmdargs = calloc(len + 1, sizeof(t_token *));
	if (!cmdargs)
		return (NULL);
	len = 0;
	while (token && token->content != NULL)
	{
		cmdargs[len] = ft_strdup(token->content);
		token = token->next;
		len++;
	}
	return (cmdargs);
}*/

