/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:19:20 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:19:20 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	ft_printf(STDOUT_FILENO, "%s\n", pwd);
	shell->exit_status = EXIT_SUCCESS;
	free(pwd);
}
