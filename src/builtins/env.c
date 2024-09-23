#include "minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
		ft_printf(1, "%s\n", shell->envp[i++]);
}
