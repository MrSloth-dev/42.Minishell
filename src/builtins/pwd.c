#include "minishell.h"

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
	printf("%s\n", pwd);
	shell->exit_status = EXIT_SUCCESS;
	free(pwd);
}
