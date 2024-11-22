/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   61_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:20:33 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:20:33 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->envp)
		return ;
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
			ft_printf(STDOUT_FILENO, "%s\n", shell->envp[i]);
		i++;
	}
}
