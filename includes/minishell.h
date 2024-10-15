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
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

# define RED "\e[1;3;31m"
# define GREEN "\e[1;3;32m"
# define YELLOW "\e[1;3;93m"
# define RESET "\e[0m"

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

//exit codes
#define EXIT_SYNTAX

//parsing errors
# define ERR_REDIR_LEFT 2
# define ERR_REDIR_RIGHT 4
# define ERR_DBLE_REDIR_LEFT 6
# define ERR_DBLE_REDIR_RIGHT 8
# define ERR_UNCLOSED_QTE 10
# define ERR_PIPE_AFTER_REDIR 12
# define ERR_PIPE 14
# define ERR_EMPTY_TOKEN 16

// token types
# define WHITE_SPACE 1
# define WORD 2
# define PIPELINE 3
# define ENV 4
# define REDIR_IN 5 //>
# define REDIR_OUT 6 //<
# define DBLE_REDIR_OUT 7 //<<
# define HERE_DOC 8
# define SINGLE_QTE 9
# define DOUBLE_QTE 10

// status
# define NORMAL 0
# define IN_SINGLE_QTE 1
# define IN_DOUBLE_QTE 2

// node classify
# define ND_EXEC 1
# define ND_PIPE 2

// classification of nodes
# define EXEC 1
# define BUILTIN 2
# define PIPE 3
# define REDIR 4

typedef struct s_token
{
	int				status;
	int				type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*left;
	struct s_token	*right;
}		t_token;

typedef struct s_token_lst
{
	t_token	*first;
	t_token	*last;
}		t_token_lst;
///////////////////////////////

///////////////////////////////
typedef struct s_shell
{
	t_token_lst	*token_lst;
	int			exit_status;
	char		*prog_name;
	char		**envp;
	char		**path;
	char		*line;
	int			pid;
}	t_shell;
/////////////////////////////
// HELPER STRUCTS
typedef struct s_iter
{
	int	i;
	int	j;
	int	k;
	int len;
}			t_iter;

// BUILT-INS
void	ft_echo(t_token *cmd_args, t_shell *sh);
void	ft_pwd(t_shell *shell);
void	ft_env(t_shell *shell);
void	ft_export(t_token *cmdargs, t_shell *shell);
void	ft_unset(t_token *cmdargs, t_shell *shell);
void	ft_cd(t_token *cmdargs, t_shell *shell);
void	ft_exit(char *pwd, t_shell *shell);

//BUILT-INS UTILS
char	*ft_get_env_key_and_value(char *env_key, t_shell *shell);
char	*ft_get_env_key(char *env_str);
char	*ft_get_env_value(char *env_name, char **env_list, t_shell *shell);
int		ft_env_exist(char *var, int *j, char **temp);
char	*ft_strjoin_free(char const *s1, char const *s2);
void	ft_append_env(char *cmdargs, char **temp);
void	ft_swap_env(char *cmdargs, char **temp, int j);
void	ft_append_env(char *cmdargs, char **temp);
void	ft_swap_env(char *cmdargs, char **temp, int j);
void	ft_swap_plus_env(char *cmdargs, char **temp, int j, t_shell *shell);
void	ft_export_no_args(t_shell shell);
int		ft_env_duplicate(t_token *cmdargs);
void	ft_free_and_exit(char *pwd, t_shell *shell);

//EXPAND
char	*ft_expand(char *str, t_shell *shell);
void	ft_make_expansions(t_shell *sh);

//init
t_shell	*ft_init_shell(char *envp[], char *argv_zero);
char	**ft_copy_envp(char **envp, int extra);

// signals_and_readline
t_shell	*ft_readline(t_shell *sh);

// syntax_utils_file
void	ft_print_syntax_error(int error);
int		ft_check_status(int status, char c);
int		ft_is_space(char c);
int		ft_is_empty_token(char *line, int direction);
// syntax
int		ft_have_unclosed_qtes(char *line);
int		ft_check_redirs(char *line);
int		ft_check_pipes(char *line);
int		ft_check_special_char(char *line);
int		ft_have_syntax_error(t_shell *sh);

//tokenizer
void	ft_tokenizer(t_token_lst *token_lst, char *line, t_shell *sh);
//tokenizer utils
int		ft_is_word(char c);
int		ft_how_much_consecutives_spaces(char *str);

//parse
t_token	*ft_make_bin_tree(t_token *token, int nd_type);

//free_stuff
void	ft_free_tree(t_token_lst *token_lst);
void 	ft_free_lst_shell(t_shell *sh); //NOT NECESSARY TO DELIVER PROJECT

//EXEC
void	ft_exec_builtins(t_token *cmdargs, t_shell *shell);
void	ft_execve(t_token *cmd, t_shell *shell);
void	ft_run_cmd(t_token *token, t_shell *shell);
int		ft_isbuiltin(char *content);

//UTILS
t_iter	set_h(int n);


//STUF TO ORGANIZE BY IVAN. NEEDED STUFF IN OTHER FILES,THAT I USED ON MY MAIN FILE
void	ft_free_envp(char **envp);

// WARNING
void	ft_print_binary_tree(t_token_lst *token_lst);
void	ft_print_tokens(t_token_lst *token_lst);

int	ft_getpid(t_shell *shell);
#endif //MINISHELL_H_
