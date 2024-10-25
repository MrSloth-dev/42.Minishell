/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_check_file_access.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:25:13 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:25:13 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_file_access(char *file, int redir, t_shell *sh)
{
	struct stat	stat_path;

	if (stat(file, &stat_path) == -1 && (redir != REDIR_OUT
			|| redir != DBLE_REDIR_OUT))
		return (ft_printf(STDERR_FILENO, "%s: %s: No such file or directory\n",
				sh->prog_name, file), 0);
	else if (redir == REDIR_IN || redir == HERE_DOC)
	{
		if (access(file, R_OK) == -1)
			return (ft_printf(STDERR_FILENO, "%s: %s: Permission denied\n",
					sh->prog_name, file), 0);
	}
	else if (redir == REDIR_OUT || redir == DBLE_REDIR_OUT)
		if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
			return (ft_printf(STDERR_FILENO, "%s: %s: Permission denied\n",
					sh->prog_name, file), 0);
	return (1);
}
