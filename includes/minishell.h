/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:12 by joao-pol          #+#    #+#             */
/*   Updated: 2024/09/20 13:24:51 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define SUCCESS 0
# define ERROR 1
# define INVALID -1

// classification of nodes
# define EXEC 1
# define BUILTIN 2
# define PIPE 3
# define REDIR 4

typedef struct s_shell
{
	char	**envp;
	int		exit_status;
}	t_shell;

// BUILT-INS
void	ft_echo(char **cmd_args, t_shell *sh);
void	ft_pwd(t_shell *shell);
void	ft_env(t_shell *shell);
char	**ft_export(char **cmdargs, t_shell *shell);
char	**ft_unset(char **cmdargs, t_shell *shell);

// 00_signals_and_readline
void	ft_readline(t_shell *sh);
#endif //MINISHELL_H_
