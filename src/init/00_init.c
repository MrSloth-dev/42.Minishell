#include "minishell.h"

t_shell	*ft_init_shell(char *envp[])
{
	t_shell	*sh;
	sh = ft_calloc(1, sizeof(t_shell));
	if (!sh)
	{
		printf("Error allocating \"*sh\" struct!\n");
		return (NULL);
	}
	sh->token_lst = NULL;
	sh->envp = envp;

	return (sh);
}
