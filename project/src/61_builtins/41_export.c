/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:19:24 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 15:19:24 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"

static int	ft_export_size_increase(t_token *cmdargs, t_shell *sh, int *j)
{
	t_token	*current;
	int		i;

	i = 0;
	*j = -1;
	current = cmdargs;
	while (sh->envp && sh->envp[i])
		i++;
	while (current)
	{
		if (ft_env_exist(current->content, j, sh->envp) == -1)
			i++;
		if (ft_env_duplicate(current) || !ft_check_valid_identifiers(current))
			i--;
		current = current->next;
	}
	return (i);
}

static int	ft_plus_mode(char *cmdargs)
{
	int	i;

	if (!ft_strchr(cmdargs, '+'))
		return (0);
	i = 0;
	while (cmdargs[i] && cmdargs[i] != '=')
	{
		if (cmdargs[i] == '+' && cmdargs[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_add_env(t_token *cmdargs, char **temp, int plus_mod, t_shell *sh)
{
	t_token	*current;
	int		j;

	current = cmdargs;
	j = -1;
	while (current && current->content)
	{
		if (!ft_valid_identifiers_msg(current, sh))
		{
			current = current->next;
			sh->exit_status = EXIT_FAILURE;
			continue ;
		}
		plus_mod = ft_plus_mode(current->content);
		if (ft_env_exist(current->content, &j, temp) != -1 && plus_mod)
			ft_swap_plus_env(current->content, temp, j, sh);
		else if (ft_env_exist(current->content, &j, temp) != -1 && !plus_mod)
			ft_swap_env(current->content, temp, j);
		else
			ft_append_env(current->content, temp);
		current = current->next;
		sh->exit_status = EXIT_SUCCESS;
	}
}

void	ft_export(t_token *cmdargs, t_shell *sh)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sh->exit_status = EXIT_SUCCESS;
	if (!cmdargs)
	{
		ft_export_no_args(*sh);
		return ;
	}
	i = ft_export_size_increase(cmdargs, sh, &j);
	temp = ft_copy_envp(sh->envp, i);
	if (!temp)
		return ;
	ft_add_env(cmdargs, temp, 0, sh);
	ft_free_envp(sh->envp);
	sh->envp = temp;
}
