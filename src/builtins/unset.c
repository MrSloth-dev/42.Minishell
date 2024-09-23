#include "minishell.h"

static int		ft_env_exist(char *var, int *j, t_shell *shell);
static char	*ft_get_var_name(char *env_str);

static void	ft_remove_env(char **temp, int j, t_shell *shell)
{
	int		k;

	k = 0;
	j--;
	while (shell->envp[k])
	{
		if (j == k)
			k++;
		else
			temp[k - 1] = ft_strdup(shell->envp[k]);
		if (!temp[k])
			return ;
		k++;
	}
}

char	**ft_unset(char **cmdargs, t_shell *shell)
{
	char	**temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 1;
	j = -1;
	if (cmdargs == NULL)
		return (NULL);
	while (cmdargs[k])
		if (ft_env_exist(cmdargs[k++], &j, shell) == -1)
			i--;
	k = 0;
	while (cmdargs[++k])
	{
		while (shell->envp[i])
			i++;
		temp = (char **)malloc(sizeof(char *) * (i + 2));
		ft_env_exist(cmdargs[k], &j, shell);
		i = 0;
		if (j != -1)
			ft_remove_env(temp, j, shell);
	}
	while (temp[i])
		printf("%s\n", temp[i++]);
	return (temp);
}

static char	*ft_get_var_name(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (i == (int)ft_strlen(env_str))
		return (NULL);
	return (ft_substr(env_str, 0, i));
}

static int	ft_env_exist(char *var, int *j, t_shell *shell)
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
