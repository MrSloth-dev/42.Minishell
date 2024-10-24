#include "ft_printf.h"
#include "minishell.h"
#include <curses.h>
#include <fcntl.h>
#include <sys/wait.h>


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

void	ft_here_doc(t_shell *sh, char *delimiter, int hd_id, char *file)
{
	char	*line;

	sh->heredoc_fd[hd_id] = open(file, O_RDWR | O_APPEND, 0644);
	sh->exit_status = EXIT_SUCCESS;
	line = NULL;
	while (1)
	{
		ft_sig_heredoc();
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf(1, "%s: warning: here-document delimited by end-of-file (wanted `%s')\n", sh->prog_name, delimiter);
			close(sh->heredoc_fd[hd_id]);
			break ;
		}
		else if (ft_strcmp(line, delimiter)  == 0)
		{
			close(sh->heredoc_fd[hd_id]);
			break ;
		}
		else if ((line && *(line)))
		{
			ft_printf(sh->heredoc_fd[hd_id], "%s", line);
			write(sh->heredoc_fd[hd_id], "\n", 1);
		}
		line = ft_free(line);
	}
}

void	ft_run_heredocs(t_token *token, t_shell *sh)
{
	t_iter	s;
	int		pid;
	int		status;

	if (!token || !sh)
		return ;
	s = ft_set_iter(0);
	s.cur = token;
	pid = fork();
	// ft_start_sig_in_this_scope();
	if (pid == 0)
	{
		ft_sig_default();
		while (s.cur)
		{		
			if (s.cur->file)
			{
				ft_here_doc(sh, s.cur->content, s.cur->hd_id, s.cur->file);
			}
			s.cur = s.cur->front;
		}
		ft_free_and_exit(NULL, sh, TRUE);
	}
	else
	{
		//waitpid(pid, NULL, 0);
		ft_sig_ignore();
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			ft_printf(1, "\n");
			sh->head = NULL;
		}
		ft_sig_default();
	}
}

void	ft_create_and_run_heredocs(t_shell *sh)
{	
	if (sh->nb_heredoc < 1)
		return ;
	ft_run_heredocs(sh->token_lst->first, sh);
}

