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
# define TRUE 3
# define FALSE 2

// parsing macros - preceded by "P_"
# define P_PIPE '|'
# define P_DOLLAR '$'
# define P_REDIR_LEFT '<'
# define P_REDIR_RIGHT '>'
# define P_SINGLE_QTE '\''
# define P_DOUBLE_QTE '"'

// status
# define NORMAL 0
# define IN_SINGLE_QTE 1
# define IN_DOUBLE_QTE 2


// classification of nodes
# define EXEC 1
# define BUILTIN 2
# define PIPE 3
# define REDIR 4

typedef struct s_shell
{
	char	*line;
	char	**envp;
	int		exit_status;
}	t_shell;

typedef struct s_token
{
	int		id;
	int		pos;
	char	*content;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

// BUILT-INS
void	ft_echo(char **cmd_args, t_shell *sh);
void	ft_pwd(t_shell *shell);
void	ft_env(t_shell *shell);
char	**ft_export(char **cmdargs, t_shell *shell);
char	**ft_unset(char **cmdargs, t_shell *shell);

// 00_signals_and_readline
t_shell	*ft_readline(t_shell *sh);
#endif //MINISHELL_H_
