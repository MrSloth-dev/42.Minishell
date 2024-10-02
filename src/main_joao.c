/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_joao.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:47:44 by joao-pol          #+#    #+#             */
/*   Updated: 2024/09/20 12:57:17 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	sh;
	char	**split;

	if (argc != 2)
		return (1);
	sh.envp = envp;
	split = ft_split(argv[1], ' ');
	// sh.envp = ft_export(split, &sh);
	ft_cd(split, &sh);
	//ft_env(&sh);
	// ft_cd(ft_split("cd -", ' '), &sh);
	// ft_cd(ft_split("cd /usr/src/python3.10/", ' '), &sh);
	// ft_pwd(&sh);
	// sh.envp = ft_unset(split, &sh);
	// ft_echo(split, &sh);
	// ft_readline();
	return (0);
}
