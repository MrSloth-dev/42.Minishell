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

void	ft_exec_builtins(char **cmdargs, t_shell *shell);

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*sh;
	char	**split;
	(void)argc;
	sh = ft_init_shell(envp);
	int i = 0;
	// chdir("..");
	// ft_printf(1, "%s\n", getcwd(NULL, 0));
	// return 0;
	while (argv[i++])
	{
		split = ft_split(argv[i], ' ');
		if (!split)
			free(split);
		else
			ft_exec_builtins(split, sh);
	}
	i = 0;
	// ft_env(sh);
	return (0);
}

void	ft_exit(t_shell *shell)
{
	free(shell->envp);
	exit(1);
}

void	ft_exec_builtins(char **cmdargs, t_shell *shell)
{
	if (!ft_strcmp("cd", cmdargs[0]))
		ft_cd(cmdargs, shell);
	else if (!ft_strcmp("export", cmdargs[0]))
		ft_export(cmdargs, shell);
	else if (!ft_strcmp("env", cmdargs[0]))
		ft_env(shell);
	else if (!ft_strcmp("pwd", cmdargs[0]))
		ft_pwd(shell);
	else if (!ft_strcmp("echo", cmdargs[0]))
		ft_echo(cmdargs, shell);
	else if (!ft_strcmp("unset", cmdargs[0]))
		ft_unset(cmdargs, shell);
	else if (!ft_strcmp("exit", cmdargs[0]))
		ft_exit(shell);
}
	// ft_printf(1, "%s\n", ft_expand(argv[i], sh));
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

