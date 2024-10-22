#include "ft_printf.h"
#include "minishell.h"
#include <curses.h>
#include <fcntl.h>
#include <sys/wait.h>

// static void	ft_handle_sig_here(int signal)
// {
// 	if (signal == SIGINT)
// 	{
//
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }
//
// static void	ft_start_sig_in_this_scope(void)
// {
// 	struct sigaction	sa;
//
// 	sa.sa_handler = &ft_handle_sig_here;
// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	sigaddset(&sa.sa_mask, SIGINT);
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }
//
void	ft_here_doc(t_shell *sh, char *delimiter, int hd_id, char *file)
{
	char	*line;

	sh->heredoc_fd[hd_id] = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	sh->exit_status = EXIT_SUCCESS;
	ft_free(file);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (sh->line == NULL || ft_strcmp(delimiter, line)  == 0)
		{
			close(sh->heredoc_fd[hd_id]);

			//ft_free_and_exit(NULL, sh, TRUE);
			break ;
		}
		else if ((line && *(line)))
		{
			ft_printf(sh->heredoc_fd[hd_id], "%s", line);
			write(sh->heredoc_fd[hd_id], "\n", 1);
		}
	}
}
void	ft_sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
void	ft_sig_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_run_heredocs(t_token *token, t_shell *sh)
{
	t_iter	s;
	char	*file;
	char	*tmp;
	int		pid_child;
	int		status;

	if (!token || !sh)
		return ;
	s = ft_set_iter(0);
	s.cur = token;
	// ft_start_sig_in_this_scope();
	while (s.cur && sh)
	{
		if (s.cur->type == HERE_DOC)
		{
			s.cur->type = REDIR_IN;
			file = ft_itoa(s.cur->hd_id);

			pid_child = fork();
			if (pid_child == 0)
			{
				ft_sig_heredoc();
				ft_here_doc(sh, s.cur->content, s.cur->hd_id, file);
				//ft_free_and_exit(NULL, sh, TRUE);
			}
			else if (pid_child > 0)
			{
				ft_sig_ignore();
				waitpid(pid_child, &status, 0);
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				{
					ft_printf(1, "\n");
					free(file);
					sh->head = NULL;
					ft_sig_default();
					return ;
				}
				tmp = s.cur->content;
				s.cur->content = file;
				free(tmp);
			}
			else
			{
				free(file);
				return ;
			}

		}
		s.cur = s.cur->front;
	}
}

void	ft_create_and_run_heredocs(t_shell *sh)
{	
	if (!(sh->nb_heredoc != 0))
		return ;
	ft_make_heredoc_fd(sh->nb_heredoc, sh);
	ft_run_heredocs(sh->token_lst->first, sh);
}

