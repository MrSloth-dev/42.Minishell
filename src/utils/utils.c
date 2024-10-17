#include "minishell.h"

int	ft_isbuiltin(char *content)
{
	if (!ft_strcmp(content, "echo"))
		return (1);
	else if (!ft_strcmp(content, "cd"))
		return (1);
	else if (!ft_strcmp(content, "pwd"))
		return (1);
	else if (!ft_strcmp(content, "export"))
		return (1);
	else if (!ft_strcmp(content, "unset"))
		return (1);
	else if (!ft_strcmp(content, "env"))
		return (1);
	else if (!ft_strcmp(content, "exit"))
		return (1);
	else
		return (0);
}
