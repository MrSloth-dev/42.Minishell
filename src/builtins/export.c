#include "libft.h"
#include "minishell.h"

char	**ft_export(char *cmdargs, t_shell *shell)
{
	char	**temp;
	int		i;

	i = 0;
	if (!*cmdargs)
		return (NULL);
	while (shell->envp[i])
		i++;
	temp = malloc(sizeof(int *) * (i + 2));
	i = 0;
	while (shell->envp[i])
	{
		temp[i] = ft_strdup(shell->envp[i]);
		if (!temp[i])
			return (NULL);
		i++;
	}
	temp[i] = ft_strdup(cmdargs);
	return (temp);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	join = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!join)
		return (free((void *)s1), free((void *)s2), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	free((void *)s1);
	free((void *)s2);
	return (join);
}
