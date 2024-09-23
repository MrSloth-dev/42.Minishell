#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <time.h>

void	ft_remove_env(char *cmdargs, char **temp, t_shell *shell);
int		ft_env_exist(char *var, int *j, t_shell *shell);
char	*ft_get_var_name(char *env_str);

void	ft_remove_env(char *cmdargs, char **temp, int j, t_shell *shell)
{
	// int		i;
	int		k;

	// i = 0;
	k = 0;
	j--;
	// while (cmdargs[i] && cmdargs[i] != '=')
	// 	i++;
	while (shell->envp[k])
	{
		if (j == k)
			temp[k] = ft_strdup(cmdargs);
		else
			temp[k] = ft_strdup(shell->envp[k]);
		if (!temp[k])
			return ;
		k++;
	}
}

char	**ft_export(char **cmdargs, t_shell *shell)
{
	char	**temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 1;
	j = -1;
	if (*cmdargs == NULL)
		return (NULL);
	while (cmdargs[k])
		if (ft_env_exist(cmdargs[k++], &j, shell) == -1)
			i++;
	k = 0;
	while (cmdargs[++k])
	{
		while (shell->envp[i])
			i++;
		temp = (char **)malloc(sizeof(char *) * (i + 2));
		ft_env_exist(cmdargs[k], &j, shell);
		i = 0;
		if (j != -1)
			ft_remove_env(cmdargs[k], temp, j, shell);
		else
			ft_remove_env(cmdargs[k], temp, shell);
		i = 0;
	}
	while (temp[i])
		printf("%s\n", temp[i++]);
	return (temp);
}

void	ft_remove_env(char *cmdargs, char **temp, t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->envp[i])
	{
		temp[i] = ft_strdup(shell->envp[i]);
		if (!temp[i])
			return ;
		i++;
	}
	temp[i++] = ft_strdup(cmdargs);
	temp[i] = 0;
}

char	*ft_get_var_name(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (i == (int)ft_strlen(env_str))
		return (NULL);
	return (ft_substr(env_str, 0, i));
}

int	ft_env_exist(char *var, int *j, t_shell *shell)
{
	char	*name;
	int		len;

	*j = 0;
	len = ft_strlen(var);
	var = ft_get_var_name(var);
	while (shell->envp[*j])
	{
		name = ft_get_var_name(shell->envp[(*j)++]);
		if (ft_strncmp(var, name, len) == 0)
			return (free(name), *j);
		free(name);
	}
	return (-1);
}

/* char	*ft_strjoin_free(char const *s1, char const *s2)
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
} */
