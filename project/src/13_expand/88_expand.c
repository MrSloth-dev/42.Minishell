/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   88_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:17:09 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:17:16 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getpid(t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		ft_free_and_exit(NULL, shell, TRUE);
	wait(0);
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
		return ((ft_itoa(shell->pid)));
	temp = ft_strjoin(str, "=");
	len = ft_strlen(temp);
	if (ft_env_exist(temp, NULL, shell->envp) == -1)
		return (ft_free(temp), ft_strdup(""));
	while (shell->envp[i])
	{
		if (ft_strncmp(temp, shell->envp[i], len) != 0)
			i++;
		else
			return (ft_free(temp),
				ft_strdup(ft_get_env_value(str, shell->envp, shell)));
	}
	return (ft_free(temp), ft_strdup(""));
}
