/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:12 by joao-pol          #+#    #+#             */
/*   Updated: 2024/09/24 17:05:30 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include "ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define SUCCESS 0
# define ERROR 1
# define INVALID -1
# define TRUE 1
# define FALSE 0

// some needed stuff
# define SINGLE 1
# define DOUBLE 2

// parsing macros - preceded by "P_"
# define P_PIPE '|'
# define P_DOLLAR '$'
# define P_REDIR_LEFT '<'
# define P_REDIR_RIGHT '>'
# define P_SINGLE_QTE '\''
# define P_DOUBLE_QTE '"'
# define LEFT_TOKEN -1
# define RIGHT_TOKEN 1

//parsing errors
# define ERR_REDIR_LEFT 2
# define ERR_REDIR_RIGHT 4
# define ERR_DBLE_REDIR_LEFT 6
# define ERR_DBLE_REDIR_RIGHT 8
# define ERR_UNCLOSED_QTE 10
# define ERR_PIPE_AFTER_REDIR 12
# define ERR_PIPE 14
# define ERR_EMPTY_TOKEN 16

// token tipes
# define WHITE_SPACE 1
# define WORD 2
# define PIPELINE 3
# define ENV 4
# define REDIR_IN 5
# define REDIR_OUT 6
# define DBLE_REDIR_OUT 7
# define HERE_DOC 8
# define SINGLE_QTE 9
# define DOUBLE_QTE 10

// status
# define NORMAL 0
# define IN_SINGLE_QTE 1
# define IN_DOUBLE_QTE 2

// classification of nodes
# define EXEC 1
# define BUILTIN 2
# define PIPE 3
# define REDIR 4

typedef struct s_token
{
	int		id;
	int		pos;
	char	*content;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_token_lst
{
	t_token	*first;
	t_token	*last;
}		t_token_lst;

typedef struct s_shell
{
	char		*line;
	char		**envp;
	int			exit_status;
	t_token_lst	*token_lst;
}	t_shell;

// BUILT-INS
void	ft_echo(char **cmd_args, t_shell *sh);
void	ft_pwd(t_shell *shell);
void	ft_env(t_shell *shell);
char	**ft_export(char **cmdargs, t_shell *shell);
char	**ft_unset(char **cmdargs, t_shell *shell);
//BUILT-INS UTILS
char	*ft_get_var_name(char *env_str);
char	*ft_get_env(char *env_name, t_shell *shell);
int	ft_env_exist(char *var, int *j, char **temp);
char	*ft_strjoin_free(char const *s1, char const *s2);
void	ft_append_env(char *cmdargs, char **temp);
void	ft_swap_env(char *cmdargs, char **temp, int j);
void	ft_append_env(char *cmdargs, char **temp);
void	ft_swap_env(char *cmdargs, char **temp, int j);

// signals_and_readline
t_shell	*ft_readline(t_shell *sh);

// syntax_utils_file
void 	ft_print_syntax_error(int	error);
int		ft_check_status(int status, char c);
int		ft_is_space(char c);
int		ft_is_empty_token(char *line, int direction);
// syntax
int		ft_have_unclosed_qtes(char *line);
int		ft_check_redirs(char *line);
int		ft_check_pipes(char *line);
int		ft_check_special_char(char *line);

#endif //MINISHELL_H_
