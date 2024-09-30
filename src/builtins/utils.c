#include "../../includes/minishell.h"
#include <stdio.h>

char	*ft_get_var_name(char *env_str)
{
	char	*substr;
	int		plus;
	int		i;

	i = 0;
	substr = ft_strchr(env_str, '+');
	printf("%s\n", substr);
	if (!substr || *(++substr) == '=')
	{
		plus = 1;
	}
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (i == (int)ft_strlen(env_str) - plus)
		return (NULL);
	return (ft_substr(env_str, 0, i));
}

char	*ft_get_env(char *env_name, t_shell *shell)
{
	char	*env;
	int		len;
	int		i;

	env = NULL;
	len = ft_strlen(env_name);
	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp(env_name, shell->envp[i], len))
		{
			env = ft_strchr(shell->envp[i], '=') + 1;
			return (env);
		}
		i++;
	}
	return (NULL);
}

int	ft_env_exist(char *var, int *j, char **env_list)
{
	char	*name;
	int		len;

	*j = 0;
	len = ft_strlen(var);
	var = ft_get_var_name(var);
	while (env_list[*j])
	{
		name = ft_get_var_name(env_list[(*j)++]);
		if (ft_strncmp(var, name, len) == 0)
			return (free(name), *j);
		free(name);
	}
	return (-1);
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
