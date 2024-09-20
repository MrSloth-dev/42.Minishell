/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_joao.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:47:44 by joao-pol          #+#    #+#             */
/*   Updated: 2024/09/16 12:28:55 by joao-pol         ###   ########.fr       */
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
	sh.envp = ft_export(split, &sh);
	// ft_env(&sh);
	// ft_echo(split, &sh);
	// ft_readline();
	return (0);
}
