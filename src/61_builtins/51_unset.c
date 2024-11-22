/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   51_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:20:27 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/29 12:26:20 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_copy_and_remove_envp(t_shell *shell, int j)
{
	char	**temp_envp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (shell->envp[i])
		i++;
	temp_envp = ft_calloc(sizeof(char *), i + 2);
	if (!temp_envp)
		return ;
	i = 0;
	while (shell->envp[i + k])
	{
		if (i == j)
			k++;
		if (!shell->envp[i + k])
			break ;
		temp_envp[i] = ft_strdup(shell->envp[i + k]);
		i++;
	}
	ft_free_envp(shell->envp);
	shell->envp = temp_envp;
}

void	ft_unset(t_token *cmdargs, t_shell *shell)
{
	t_token	*current;
	int		j;

	current = cmdargs;
	j = -1;
	if (!current)
		return ;
	while (current)
	{
		if (ft_env_exist(current->content, &j, shell->envp) != -1)
			ft_copy_and_remove_envp(shell, j);
		current = current->next;
	}
	shell->exit_status = EXIT_SUCCESS;
}
