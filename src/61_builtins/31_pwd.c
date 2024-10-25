#include "minishell.h"
#include <unistd.h>

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	ft_printf(STDOUT_FILENO, "%s\n", pwd);
	shell->exit_status = EXIT_SUCCESS;
	free(pwd);
}
