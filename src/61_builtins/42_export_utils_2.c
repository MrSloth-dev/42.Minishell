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
			return (ft_printf(1, "dup"));
		cmdargs = cmdargs->prev;
	}
	return (0);
}

void	ft_join_env(char *cmdargs, char **temp, int j)
{
	int		k;
	char	*start;

	start = NULL;
	k = 0;
	j--;
	while (temp[k])
	{
		if (j == k)
		{
			start = ft_strchr(&cmdargs[k], '=');
			temp[k] = ft_strjoin(temp[k], ++start);
		}
		if (!temp[k])
			return ;
		k++;
	}
}
