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

char	**ft_init_envp(char **envp, t_shell *shell)
{
	int	i;
	char **temp_envp;

	i = 0;
	while (envp[i])
		i++;
	temp_envp = calloc(sizeof(char *), i + 1);
	if (!temp_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		temp_envp[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	return (temp_envp);

}
