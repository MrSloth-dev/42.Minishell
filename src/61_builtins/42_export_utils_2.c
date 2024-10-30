/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:20:12 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:20:12 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_duplicate(t_token *cmdargs)
{
	char	*temp;

	temp = cmdargs->content;
	cmdargs = cmdargs->prev;
	while (cmdargs)
	{
		if (ft_strcmp(cmdargs->content, temp) == 0)
			return (1);
		cmdargs = cmdargs->prev;
	}
	return (0);
}

static int	ft_valid_first_char(t_token *cmdargs)
{
	if (!cmdargs || !cmdargs->content)
		return (0);
	if (ft_strchr("=+", cmdargs->content[0]))
		return (0);
	if (!ft_isalpha(cmdargs->content[0]) && cmdargs->content[0] != '_')
		return (0);
	if (!ft_strchr(cmdargs->content, '=') && ft_strchr(cmdargs->content, '+'))
		return (0);
	return (1);
}

int	ft_check_valid_identifiers(t_token *cmdargs)
{
	int	i;

	if (ft_valid_first_char(cmdargs) == 0)
		return (0);
	i = 0;
	while (cmdargs->content[i] && cmdargs->content[i] != '=')
	{
		if (cmdargs->content[i] == '+' && cmdargs->content[i + 1] != '=')
			return (0);
		else if (ft_isalnum(cmdargs->content[i]) || cmdargs->content[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_valid_identifiers_msg(t_token *cmdargs, t_shell *sh)
{
	int	i;

	if (ft_valid_first_char(cmdargs) == 0)
		return (ft_printf(STDERR_FILENO, INV_ID,
				sh->prog_name, cmdargs->content), 0);
	i = 0;
	while (cmdargs->content[i] && cmdargs->content[i] != '=')
	{
		if (cmdargs->content[i] == '+' && cmdargs->content[i + 1] != '=')
			return (ft_printf(STDERR_FILENO, INV_ID,
					sh->prog_name, cmdargs->content), 0);
		else if (ft_isalnum(cmdargs->content[i]) || cmdargs->content[i] == '_'
			|| cmdargs->content[i] == '+')
			i++;
		else
			return (ft_printf(STDERR_FILENO, INV_ID,
					sh->prog_name, cmdargs->content), 0);
	}
	return (1);
}
