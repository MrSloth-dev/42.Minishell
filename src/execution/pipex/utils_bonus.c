/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:05:13 by joao-pol          #+#    #+#             */
/*   Updated: 2024/07/17 13:24:00 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_path(char *envp[])
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	ft_check_quotes(char **cmd_args)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (cmd_args[i])
	{
		while (cmd_args[i][j])
		{
			if (cmd_args[i][j] == '\'')
				count++;
			j++;
		}
		if (count % 2 != 0)
		{
			ft_free(cmd_args, j);
			return (0);
		}
		j = 0;
		i++;
	}
	return (1);
}
