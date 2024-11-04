/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:20:06 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:20:06 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_value(char *env_name, char **env_list, t_shell *shell);

void	ft_swap_plus_env(char *cmdargs, char **temp, int j, t_shell *shell)
{
	char	*joinvalue;

	if (!ft_strchr(cmdargs, '='))
		joinvalue = ft_strdup("");
	else
		joinvalue = ft_strchr(cmdargs, '=') + 1;
	if (ft_strchr(temp[j], '='))
		temp[j] = ft_strjoin_free(temp[j], ft_strdup(joinvalue));
	else
	{
		temp[j] = ft_strjoin_free(temp[j], ft_strdup("="));
		temp[j] = ft_strjoin_free(temp[j], ft_strdup(joinvalue));
	}
	shell->exit_status = EXIT_SUCCESS;
}

void	ft_swap_env(char *cmdargs, char **temp, int j)
{
	int		k;

	k = 0;
	if (!ft_strchr(cmdargs, '='))
		return ;
	while (temp[k])
	{
		if (j == k)
		{
			free(temp[k]);
			temp[k] = ft_strdup(cmdargs);
		}
		if (!temp[k] || j == k)
			return ;
		k++;
	}
}

void	ft_append_env(char *cmdargs, char **temp)
{
	int		i;
	char	*plus_str;

	i = 0;
	while (temp[i])
		i++;
	if (ft_strchr(cmdargs, '+'))
	{
		if (*(ft_strchr(cmdargs, '=') + 1) != 0)
		{
			plus_str = ft_get_env_key(cmdargs);
			plus_str = ft_strjoin_free(plus_str, ft_strdup("="));
			plus_str = ft_strjoin_free(plus_str,
					ft_strdup(ft_strchr(cmdargs, '=') + 1));
			temp[i] = ft_strdup(plus_str);
			ft_free(plus_str);
		}
		else
		{
			*ft_strchr(cmdargs, '+') = 0;
			temp[i] = ft_strdup(cmdargs);
		}
	}
	else
		temp[i] = ft_strdup(cmdargs);
}

char	**ft_order_env(char **env)
{
	char	**order;
	char	*swap;
	int		size;
	int		i;

	i = 0;
	size = 0;
	if (!env)
		return (NULL);
	order = ft_copy_envp(env, 0);
	while (order[size])
		size++;
	while (i < size - 1)
	{
		if (ft_strcmp(order[i], order[i + 1]) > 0)
		{
			swap = order[i];
			order[i] = order[i + 1];
			order[i + 1] = swap;
			i = 1;
		}
		else
			i++;
	}
	return (order);
}

void	ft_export_no_args(t_shell shell)
{
	int		i;
	char	**order;
	char	*value;
	char	*key;

	if (!shell.envp)
		return ;
	order = ft_order_env(shell.envp);
	i = -1;
	while (order && order[++i])
	{
		key = ft_get_env_key(order[i]);
		ft_printf(STDOUT_FILENO, "declare -x %s", key);
		value = ft_extract_value(order[i], order, &shell);
		if (!value)
			ft_printf(STDOUT_FILENO, "\n");
		else
			ft_printf(STDOUT_FILENO, "=\"%s\"\n", value);
		ft_free(key);
	}
	ft_free_envp(order);
}
