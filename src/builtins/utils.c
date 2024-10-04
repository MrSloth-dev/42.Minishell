#include "../../includes/minishell.h"
#include "ft_printf.h"

char	*ft_get_env_key_and_value(char *env_key, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(env_key);
	while (*shell->envp)
		if (ft_strncmp(env_key, ft_get_env_key(*shell->envp++), len) == 0)
			return (shell->envp[i]);
	return (NULL);
}

char	*ft_get_env_key(char *env_str)
{
	char	*substr;
	int		plus;
	int		i;

	i = 0;
	plus = 0;
	substr = ft_strchr(env_str, '+');
	if (substr && *(++substr) == '=')
		plus = 1;
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (i == (int)ft_strlen(env_str) - plus)
		return (NULL);
	return (ft_substr(env_str, 0, i));
}

char	*ft_get_env_value(char *env_name, char **env_list, t_shell *shell)
{
	char	*env;
	int		len;
	int		i;

	if (!env_name)
		return (NULL);
	env = NULL;
	len = ft_strlen(env_name);
	i = 0;
	shell->exit_status = EXIT_SUCCESS;
	while (env_list[i])
	{
		if (!ft_strncmp(env_name, env_list[i], len))
		{
			env = ft_strchr(env_list[i], '=') + 1;
			if (!env)
				return (ft_strdup(""));
			else
				return (env);
		}
		i++;
	}
	return (ft_strdup(""));
}

int	ft_env_exist(char *var, int *j, char **env_list)
{
	char	*name;
	char	*key;
	int		len;
	int		index;

	if (!var)
		return (-1);
	index = 0;
	key = ft_get_env_key(var);
	if (key == NULL)
		return (-1);
	len = ft_strlen(key);
	while (env_list[index])
	{
		name = ft_get_env_key(env_list[index]);
		if (!name && index++)
			continue ;
		if (ft_strncmp(key, name, len) == 0)
		{
			if (j)
				*j = index;
			return (free(name), free(key), index);
		}
		free(name);
		index++;
	}
	return (free(key), -1);
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
