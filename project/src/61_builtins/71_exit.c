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

#include "ft_printf.h"
#include "minishell.h"

static long long	ft_atoll(const char *str);

static void	ft_numeric_argument_print(t_shell *sh, t_token *token)
{
	ft_printf(STDERR_FILENO,
		"%s : exit : %s: numeric argument required\n",
		sh->prog_name, token->content);
}

static int	ft_invalid_exit_code(t_token *token, t_shell *sh)
{
	int	i;
	int	exit_status;

	if (token && token->next)
		return (sh->exit_status = 1, 1);
	i = 0;
	if (token->content[0] == '-' || token->content[0] == '+')
		i++;
	exit_status = 0;
	if (!token->content[i]
		|| ft_strcmp(token->content, "9223372036854775808") == 0)
	{
		ft_numeric_argument_print(sh, token);
		return (sh->exit_status = 2, 2);
	}
	while (token && token->content[i] && ft_strcmp(token->content, "--") != 0)
	{
		if (!ft_isdigit(token->content[i]))
		{
			ft_numeric_argument_print(sh, token);
			return (sh->exit_status = 2, 2);
		}
		i++;
	}
	return (exit_status);
}

void	ft_exit(t_token *token, t_shell *sh)
{
	int	exit_status;

	if (token && sh->head->type != ND_PIPE)
		ft_printf(STDOUT_FILENO, "exit\n");
	if (!token)
	{
		sh->exit_status = 0;
		ft_free_and_exit(token, sh, TRUE);
	}
	exit_status = ft_invalid_exit_code(token, sh);
	if (exit_status == 0)
		sh->exit_status = (unsigned char)ft_atoll(token->content);
	else if (exit_status == 1)
	{
		ft_printf(STDERR_FILENO,
			"%s : exit : too many arguments\n", sh->prog_name);
		sh->exit_status = 1;
		return ;
	}
	else
		sh->exit_status = exit_status;
	ft_free_and_exit(token, sh, TRUE);
}

static long long	ft_atoll(const char *str)
{
	long long	res;
	int			neg;
	int			i;

	neg = 1;
	res = 0;
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * neg);
}
