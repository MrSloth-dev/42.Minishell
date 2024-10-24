#include "minishell.h"

int	ft_print_execve_error(int error, t_token *token, t_shell *shell)
{
	if (error == 127)
	{
		if ((token->content[0] == '.' && token->content[1] == '/')
				|| token->content[0] == '/')
		{
			ft_printf(STDERR_FILENO, "%s : No such file or directory\n", token->content);
			return (shell->exit_status = 127, 127);
		}
		else
		{
			ft_printf(STDERR_FILENO, "%s : command not found\n", token->content);
			return (shell->exit_status = 127, 127);
		}
	}
	else if (error == 128)
	{
		if (!ft_strchr(token->content, '/'))
		{
			ft_printf(STDERR_FILENO, "%s : command not found\n", token->content);
			return (shell->exit_status = 127, 127);
		}
		else
		{
			ft_printf(STDERR_FILENO, "%s : Is a directory\n", token->content);
			return (shell->exit_status = 126, 126);
		}
	}
	else if (error == 126)
	{
		if ((token->content[0] == '.' && token->content[1] == '/')
				|| token->content[0] == '/')
		{
			ft_printf(STDERR_FILENO, "%s : Permission denied\n", token->content);
			return (shell->exit_status = 126, 126);
		}
		else
		{
			ft_printf(STDERR_FILENO, "%s : command not found\n", token->content);
			return (shell->exit_status = 127, 127);
		}
	}
	return (0);
}
