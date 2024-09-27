#include "ft_printf.h"
#include "minishell.h"

void	ft_append_env(char *cmdargs, char **temp);
int		ft_env_exist(char *var, int *j, char **temp);
char	*ft_get_var_name(char *env_str);

void	ft_swap_env(char *cmdargs, char **temp, int j)
{
	int		k;

	k = 0;
	j--;
	while (temp[k])
	{
		if (j == k)
			temp[k] = ft_strdup(cmdargs);
		if (!temp[k])
			return ;
		k++;
	}
}

void	ft_join_env(char *cmdargs, char **temp, int j)
{
	int		k;
	int		start;

	start = 0;
	k = 0;
	j--;
	while (temp[k])
	{
		if (j == k)
		{
			start = ft_strchr(cmdargs[k], '=');
			temp[k] = ft_strjoin(temp[k], ft_strchr(cmdargs[k], '+')++);
		}
		if (!temp[k])
			return ;
		k++;
	}
}

void	ft_copy_env(char **temp, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		temp[i] = ft_strdup(env[i]);
}

static int	ft_export_duplicate(char **cmdargs, int k)
{
	char	*temp;

	temp = cmdargs[k];
	while (--k)
		if (cmdargs[k] == temp)
			return (1);
	return (0);
}

static int	ft_export_size_increase(char **cmdargs, t_shell *shell, int *j)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	*j = -1;
	while (shell->envp[i])
		i++;
	while (cmdargs[k])
	{
		if (ft_env_exist(cmdargs[k++], j, shell->envp) == -1)
			i++;
		if (ft_export_duplicate(cmdargs, k))
			i--;
	}
	return (i);
}

char	**ft_export(char **cmdargs, t_shell *shell)
{
	char	**temp;
	int		i;
	int		j;
	int		k;
	int		plus_mode;

	if (!cmdargs)
		return (NULL);
	plus_mode = 0;
	i = ft_export_size_increase(cmdargs, shell, &j);
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	ft_copy_env(temp, shell->envp);
	k = 0;
	while (cmdargs[++k])
	{
		j = -1;
		if ((ft_strchr(cmdargs[k], '=') - ft_strchr(cmdargs[k], '+')) == 1)
			plus_mode = 1;
		if (ft_env_exist(cmdargs[k], &j, temp) != -1 && plus_mode)
			ft_swap_env(cmdargs[k], temp, j);
		else if (ft_env_exist(cmdargs[k], &j, temp) != -1 && !plus_mode)
			ft_swap_env(cmdargs[k], temp, j);
		else
			ft_append_env(cmdargs[k], temp);
	}
	return (temp);
}

void	ft_append_env(char *cmdargs, char **temp)
{
	int		i;

	i = 0;
	while (temp[i])
		i++;
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

int	ft_env_exist(char *var, int *j, char **temp)
{
	char	*name;
	int		len;

	*j = 0;
	len = ft_strlen(var);
	var = ft_get_var_name(var);
	while (temp[*j])
	{
		name = ft_get_var_name(temp[(*j)++]);
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
