#include "ft_printf.h"
#include "minishell.h"

char	*ft_find_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) != 0)
			envp++;
		else
			return (*envp + 5);
	}
	return (NULL);
}

t_shell	*ft_init_shell(char *envp[], char *argv_zero)
{
	t_shell	*sh;

	sh = ft_calloc(1, sizeof(t_shell));
	if (!sh)
	{
		printf("Error allocating \"*sh\" struct!\n");
		return (NULL);
	}
	// sh->pid = ft_getpid(sh);
	sh->prog_name = argv_zero;
	sh->token_lst = NULL;
	sh->envp = ft_copy_envp(envp, 0);
	sh->path = ft_split(ft_find_path(sh->envp), ':'); //LEAKS come from HERE 11november
	return (sh);
}

char	**ft_copy_envp(char **envp, int extra)
{
	char	**temp_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	temp_envp = ft_calloc(sizeof(char *), i + extra + 1);
	if (!temp_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		temp_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	while (extra-- > 0)
		temp_envp[i++] = 0;
	temp_envp[i] = 0;
	return (temp_envp);
}
