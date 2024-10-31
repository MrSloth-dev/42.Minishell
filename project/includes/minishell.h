/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:12 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/29 11:48:26 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

# define RED "\e[1;3;31m"
# define GREEN "\e[1;3;32m"
# define YELLOW "\e[1;3;93m"
# define RESET "\e[0m"

# ifndef PRINT_DATA
#  define PRINT_DATA 0
# endif

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
# define EXIT_SYNTAX

//parsing errors
# define ERR_REDIR_LEFT 2
# define ERR_REDIR_RIGHT 4
# define ERR_DBLE_REDIR_LEFT 6
# define ERR_DBLE_REDIR_RIGHT 8
# define ERR_UNCLOSED_QTE 10
# define ERR_PIPE_AFTER_REDIR 12
# define ERR_PIPE 14
# define ERR_EMPTY_TOKEN 16

// status
# define NORMAL 0
# define IN_SINGLE_QTE 1
# define IN_DOUBLE_QTE 2

// node classify
# define WHITE_SPACE 1
# define WORD 2
//# define EMPTY 3
# define ENV 4
# define SINGLE_QTE 5
# define DOUBLE_QTE 6
# define ND_EXEC 7
# define ND_PIPE 8
//# define ND_REDIR 9
# define HERE_DOC 11 //
# define REDIR_IN 12 //>
# define REDIR_OUT 13 //<
# define DBLE_REDIR_OUT 14 //>>
//
// classification of nodes
# define EXEC 1
# define BUILTIN 2
# define PIPE 3
# define REDIR 4

// SHORTEN MESSAGES
# define INV_ID "%s : export : `%s': not a valid identifier\n"

///////////////////////////////
//      NODE STRUCT         //
//////////////////////////////
extern int	g_rec_signal;

///////////////////////////////
//      NODE STRUCT         //
///////////////////////////////
typedef struct s_token
{
	int				status;
	int				type;
	int				hd_id;
	int				maybe_to_delete;
	char			*file;
	char			*content;
	struct s_token	*front;
	struct s_token	*back;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*left;
	struct s_token	*right;
}		t_token;

typedef struct s_token_lst
{
	t_token	*first;
}		t_token_lst;
///////////////////////////////
//      MAIN STRUCT         //
///////////////////////////////
typedef struct s_shell
{
	char		*hostname;
	char		*user;
	int			std_in;
	int			std_out;
	t_token_lst	*token_lst;
	t_token		*head;
	long		exit_status;
	char		*prog_name;
	char		**envp;
	char		**path;
	char		*line;
	int			pid;
	char		*hd_path;
	int			nb_heredoc;
	int			*heredoc_fd;
	int			ambig_redir;
}	t_shell;
/////////////////////////////
//      HELPER STRUCT      //
/////////////////////////////
typedef struct s_iter
{
	char		c;
	int			i;
	int			j;
	int			k;
	int			fd;
	int			std_in;
	int			std_out;
	int			pid;
	int			len;
	int			status;
	char		*delimiter;
	char		*file;
	char		*prog_name;
	char		*exp;
	char		*name_var;
	char		*str;
	char		*line;
	t_token		*tmp;
	t_token		*cur;
	t_token		*cur_left;
	t_token		*cur_right;
	t_token		*front;
	t_token		*back;
	t_token_lst	*new_lst;
	char		**split;
}				t_iter;

//00_INIT/
t_shell	*ft_init_shell(char *envp[], int ac, char *av[], t_shell *sh);
char	**ft_copy_envp(char **envp, int extra);
//01_SIGNALS_AND_READLINE/
t_shell	*ft_readline(t_shell *sh);
void	ft_sig_restore(void);
void	ft_sig_child(void);
void	ft_sig_mute(void);
int		ft_get_exit_status(int exit_code, t_shell *sh);
//11_SYNTAX/
void	ft_print_syntax_error(int error, t_shell *shell);
int		ft_check_status(int status, char c);
int		ft_is_space(char c);
int		ft_is_empty_token(char *line, int direction);
int		ft_have_syntax_error(t_shell *sh);
int		ft_have_unclosed_qtes(char *line);
int		ft_check_redirs(char *line);
int		ft_check_pipes(char *line);
int		ft_check_special_char(char *line);
//12_TOKENIZER/
void	ft_create_tokens(t_token_lst *token_lst, char *line);
t_token	*ft_new_token(void);
int		ft_append_node(t_token_lst *token_lst, char *str, int type, int status);
int		ft_append_word(t_token_lst *token_lst, char *str, int type, int status);
int		ft_append_redir(t_token_lst *token_lst, char *line, int status);
void	ft_join_tokens(t_token_lst *token_lst);
void	ft_join_heredoc_to_words(t_token_lst *token_lst);
void	ft_delete_spaces(t_token_lst *token_lst, t_shell *sh);
void	ft_add_node_exec(t_token_lst *token_lst, t_shell *sh);
void	ft_convert_empty_strings(t_token *token);
int		ft_is_word(char c);
int		ft_how_much_consecutives_spaces(char *str);
//13_EXPAND/
void	ft_make_expansions(t_shell *sh);
void	ft_delete_null_expansions_if_needed(t_shell *sh);
void	ft_split_this_node(t_iter *out);
void	ft_split_tokens_with_white_spaces(t_shell *sh);
int		ft_getpid(t_shell *shell);
char	*ft_expand(char *str, t_shell *shell);
//31_PARSE_DATA/
t_token	*ft_make_bin_tree(t_token *token);
//32_HERE_DOC/
void	ft_do_heredoc_files(t_token *token, t_shell *sh);
int		ft_here_doc(char delimiter[4096], char file[4096]);
int		ft_run_heredocs(t_token *token, t_shell *sh);
void	ft_free_inside_heredoc(t_shell *sh);
void	ft_get_file_name(char hd_file[4096], char *src_file);
void	ft_get_delimiter(char delimiter[4096], char *content);
//33_AMBIGUOUS_REDIR/
void	ft_check_ambiguous_redir(t_token *token, t_shell *sh);
void	ft_print_ambiguous_redir_msg(t_shell *sh);
//51_EXECUTION/
void	ft_run(t_token *token, t_shell *sh);
int		ft_exec_redir(t_token *cur_redir, t_shell *sh);
void	ft_restore_fd(int std_in, int std_out, t_shell *sh);
void	ft_multiple_close(int fd1, int fd2);
int		ft_get_exit_signal(int *exit, t_shell *sh);
void	ft_close_pipe(int exit[2], int pid[2], int pipe[2], t_shell *sh);
void	ft_exec_builtins(t_token *temp_head, t_shell *shell);
void	ft_exec_builtins_child(t_token *cmdargs, t_shell *sh);
void	ft_exec_builtins_parent(t_token *cmdargs, t_shell *sh);
void	ft_execve(t_token *cmd, t_shell *shell);
//61_BUILTINS/
int		ft_echo(t_token *cmdargs, t_shell *sh);
void	ft_cd(t_token *cmdargs, t_shell *shell);
void	ft_pwd(t_shell *shell);
void	ft_export(t_token *cmdargs, t_shell *shell);
void	ft_swap_plus_env(char *cmdargs, char **temp, int j, t_shell *shell);
void	ft_swap_env(char *cmdargs, char **temp, int j);
void	ft_append_env(char *cmdargs, char **temp);
char	**ft_order_env(char **env);
void	ft_export_no_args(t_shell shell);
char	*ft_extract_value(char *env_name, char **env_list, t_shell *shell);
int		ft_env_duplicate(t_token *cmdargs);
int		ft_check_valid_identifiers(t_token *cmdargs);
int		ft_valid_identifiers_msg(t_token *cmdargs, t_shell *sh);
void	ft_unset(t_token *cmdargs, t_shell *shell);
void	ft_env(t_shell *shell);
void	ft_exit(t_token *token, t_shell *sh);
char	*ft_get_env_key_and_value(char *env_key, t_shell *shell);
char	*ft_get_env_key(char *env_str);
char	*ft_get_env_value(char *env_name, char **env_list, t_shell *shell);
int		ft_env_exist(char *var, int *j, char **env_list);
char	*ft_strjoin_free(char const *s1, char const *s2);
//71_PRINT_MSG/
int		ft_check_file_access(char *file, int redir, t_shell *sh);
int		ft_print_execve_error(int error, t_token *token, t_shell *sh);
//81_UTILS/
t_iter	ft_set_iter(int n);
int		ft_isbuiltin(char *content);
//88_FREE_STUFF/
void	ft_free_and_exit(t_token *token, t_shell *sh, int exit_flag);
void	*ft_free(void *pointer);
void	ft_free_tokens(t_shell *sh);
void	*ft_free_envp(char	**envp);
void	ft_clean_hd_files(t_shell *sh);
#endif //MINISHELL_H_
