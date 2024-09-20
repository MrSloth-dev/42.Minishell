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

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	sh;

	(void)argc;
	sh.envp = envp;
	char	*str= argv[1];
	char	**split = ft_split(str, ' ');
	// ft_pwd(&sh);
	// if (ft_strncmp(split[0], "env", 3))
	// 	ft_env(&sh);
	// else if (ft_strncmp(split[0], "export", 6))
	// 	sh.envp = ft_export(split, &sh);
	// else if (ft_strncmp(split[0], "unset", 5))
		sh.envp = ft_unset(split, &sh);
	// ft_echo(split, &sh);
	// ft_readline();
	return (0);
}
