#include "minishell.h"

int	ft_getpid(t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		ft_exit (NULL, shell);
	wait(NULL);
	pid = pid - 1;
	return (pid);
}

char	*ft_expand(char *str, t_shell *shell)
{
	int		len;
	char	*temp;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (!str[0])
		return (str);
	if (ft_strncmp(str, "$", 1) == 0)
		return (ft_strdup(ft_itoa(ft_getpid(shell))));
	temp = ft_strjoin(str, "=");
	len = ft_strlen(temp);
	if (ft_env_exist(temp, NULL, shell->envp) == -1)
		return (ft_strdup(""));
	while (shell->envp[i])
	{
		if (ft_strncmp(temp, shell->envp[i], len) != 0)
			i++;
		else
			return (free(temp), ft_strdup(ft_get_env_value(str, shell->envp, shell)));
	}
	return (free(temp), ft_strdup(""));
}
