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
#include <unistd.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	sh;
	char	**split;
	char	*str;

	(void)argc;
	sh.envp = envp;
	str = argv[1];
	split = ft_split(str, ' ');
	// sh.envp = ft_export(split, &sh);
	// ft_env(&sh);
	ft_cd(split, &sh);
	str = "cd -";
	split = ft_split(str, ' ');
	ft_cd(split, &sh);
	// ft_pwd(&sh);
	// sh.envp = ft_unset(split, &sh);
	// ft_echo(split, &sh);
	// ft_readline();
	return (0);
}
