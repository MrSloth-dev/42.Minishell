/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_print_execve_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:38:10 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:38:10 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_error_not_found(t_token *token, t_shell *sh)
{
	if ((token->content[0] == '.' && token->content[1] == '/')
		|| token->content[0] == '/')
	{
		ft_printf(STDERR_FILENO, "%s : No such file or directory\n",
			token->content);
		return (sh->exit_status = 127, 127);
	}
	else
	{
		ft_printf(STDERR_FILENO, "%s : command not found\n", token->content);
		return (sh->exit_status = 127, 127);
	}
}

static int	ft_error_is_dir(t_token *token, t_shell *sh)
{
	if (!ft_strchr(token->content, '/'))
	{
		ft_printf(STDERR_FILENO, "%s : command not found\n", token->content);
		return (sh->exit_status = 127, 127);
	}
	else
	{
		ft_printf(STDERR_FILENO, "%s : Is a directory\n", token->content);
		return (sh->exit_status = 126, 126);
	}
}

static int	ft_error_permission(t_token *token, t_shell *sh)
{
	if ((token->content[0] == '.' && token->content[1] == '/')
		|| token->content[0] == '/')
	{
		ft_printf(STDERR_FILENO, "%s : Permission denied\n", token->content);
		return (sh->exit_status = 126, 126);
	}
	else
	{
		ft_printf(STDERR_FILENO, "%s : command not found\n", token->content);
		return (sh->exit_status = 127, 127);
	}
}

int	ft_print_execve_error(int error, t_token *token, t_shell *sh)
{
	if (error == 127)
		return (ft_error_not_found(token, sh));
	else if (error == 128)
		return (ft_error_is_dir(token, sh));
	else if (error == 126)
		return (ft_error_permission(token, sh));
	return (0);
}
