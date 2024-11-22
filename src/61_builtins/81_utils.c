/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   81_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:21:02 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/29 11:57:14 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*sub;
	int		plus;
	int		i;

	i = 0;
	plus = 0;
	if (!ft_strchr(env_str, '='))
		return (ft_strdup(env_str));
	sub = ft_strchr(env_str, '+');
	if (sub && *(++sub) == '=')
		plus = 1;
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (i == (int)ft_strlen(env_str) - plus + 1)
		return (NULL);
	return (ft_substr(env_str, 0, i - plus));
}

char	*ft_get_env_value(char *env_name, char **env_list, t_shell *shell)
{
	char	*env;
	int		i;
	int		len;
	char	*temp;

	if (!env_name || !env_list)
		return (NULL);
	temp = ft_strjoin(env_name, "=");
	len = ft_strlen(temp);
	env = NULL;
	i = 0;
	while (env_list[i] && *env_list[i])
	{
		if (ft_strncmp(env_list[i], temp, len) == 0
			&& ft_strchr(env_list[i], '='))
		{
			env = ft_strchr(env_list[i], '=') + 1;
			if (!env || !ft_strchr(env_list[i], '='))
				return ((void)shell, ft_free(temp), "");
			else
				return (ft_free(temp), env);
		}
		i++;
	}
	return (ft_free(temp), "");
}

int	ft_env_exist(char *var, int *j, char **env_list)
{
	char	*name;
	char	*key;
	int		index;

	if (!var)
		return (-1);
	index = 0;
	key = ft_get_env_key(var);
	if (!key || key[0] == 0)
		return (free(key), -1);
	while (env_list[index])
	{
		name = ft_get_env_key(env_list[index]);
		if (!name && index++)
			continue ;
		if (ft_strcmp(key, name) == 0)
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
