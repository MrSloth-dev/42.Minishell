#include "minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
		printf("%s\n", shell->envp[i++]);
}
