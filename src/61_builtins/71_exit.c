/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   71_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:20:49 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:20:49 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_invalid_exit_code(t_token *token, t_shell *sh)
{
	int	i;
	int	exit_status;

	if (token && token->next)
	{
		return (sh->exit_status = 1, 1);
	}
	i = 0;
	exit_status = 0;
	if (!ft_isdigit(token->content[0]) || token->content[0] == '+')
		i++;
	while (token && token->content[i])
	{
		if (!ft_isdigit(token->content[i++]))
		{
			ft_printf(STDERR_FILENO,
				"%s : exit : %s : numeric argument required\n",
				sh->prog_name, token->content);
			return (sh->exit_status = 2, 2);
		}
	}
	return (exit_status);
}

void	ft_exit(t_token *token, t_shell *sh)
{
	int	exit_status;

	if (!token)
	{
		sh->exit_status = 0;
		ft_free_and_exit(token, sh, TRUE);
	}
	exit_status = ft_invalid_exit_code(token, sh);
	if (exit_status == 0)
		sh->exit_status = (unsigned char)ft_atoi(token->content);
	else if (exit_status == 1)
	{
		ft_printf(STDOUT_FILENO, "exit\n");
		ft_printf(STDERR_FILENO,
			"%s : exit : too many arguments\n", sh->prog_name);
		sh->exit_status = 1;
		return ;
	}
	else
		sh->exit_status = exit_status;
	ft_printf(STDOUT_FILENO, "exit\n");
	ft_free_and_exit(token, sh, TRUE);
}
