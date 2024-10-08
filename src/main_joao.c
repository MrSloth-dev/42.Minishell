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

#include "ft_printf.h"
#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*sh;
	char	**split;
	(void)argc;
	sh = ft_init_shell(envp);
	int i = 0;
	while (argv[i++])
	{
		split = ft_split(argv[i], ' ');
		if (!split)
			free(split);
		else
			ft_cd(split, sh);
	}
	i = 0;
	// ft_env(sh);
	return (0);
}
	// split = ft_split(argv[1], ' ');
	// // ft_printf(1, "%s\n", str);
	// sh.envp = ft_export(split, &sh);
	// str = argv[2];
	// split = ft_split(str, ' ');
	// sh.envp = ft_export(split, &sh);
	// ft_cd(split, &sh);
	// ft_env(&sh);
	// ft_cd(ft_split("cd -", ' '), &sh);
	// ft_cd(ft_split("cd /usr/src/python3.10/", ' '), &sh);
	// ft_pwd(&sh);
	// sh.envp = ft_unset(split, &sh);
	// ft_echo(split, &sh);
	// ft_readline();

