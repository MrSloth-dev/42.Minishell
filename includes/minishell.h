/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:56:06 by joao-pol          #+#    #+#             */
/*   Updated: 2024/09/16 12:31:15 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H_
# define MINISHELL_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

#define SUCCESS 0
#define ERROR 1
#define INVALID -1


typedef struct s_shell
{
	char **envp;
	int exit_status;
} t_shell;




// BUILT-INS
void	ft_echo(char **cmd_args, t_shell *sh);
void	ft_pwd(t_shell *shell);
void	ft_env(t_shell *shell);
char 	**ft_export(char *cmdargs, t_shell *shell);

// 00_signals_and_readline
void	ft_readline();
#endif //MINISHELL_H_

