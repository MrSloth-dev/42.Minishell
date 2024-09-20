/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:12 by joao-pol          #+#    #+#             */
/*   Updated: 2024/09/20 12:22:02 by joao-pol         ###   ########.fr       */
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
# define TRUE 1
# define FALSE 0

# define PIPE '|'
# define DOLLAR '$'
# define R_LEFT '<'
# define R_RIGHT '>'

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

// 00_signals_and_readline
t_shell	*ft_readline(t_shell *sh);
#endif //MINISHELL_H_
