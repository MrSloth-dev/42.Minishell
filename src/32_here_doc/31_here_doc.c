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

void	ft_here_doc(char *prog_name, char *delimiter, int hd_id, char *file)
{
	char	*line;
	//sh->exit_status = EXIT_SUCCESS;
	line = NULL;
	while (1)
	{
		ft_sig_heredoc();
		line = readline("> ");
		hd_id = open(file, O_RDWR | O_APPEND, 0644);
		if (line == NULL)
		{
			ft_printf(1, "%s: warning: here-document delimited by end-of-file (wanted `%s')\n", prog_name, delimiter);
			close(hd_id);
			break ;
		}
		else if (ft_strcmp(line, delimiter)  == 0)
		{
			close(hd_id);
			break ;
		}
		else if ((line || *(line)))
		{
			ft_printf(hd_id, "%s", line);
			write(hd_id, "\n", 1);
			close(hd_id);
		}
		line = ft_free(line);
	}
}

void	ft_free_heredoc(t_shell *sh)
{
	if (!sh)
		return ;
	sh->line = ft_free(sh->line);
	ft_free_lst_shell(sh);
	sh->token_lst = ft_free(sh->token_lst);
		if (sh->envp)
			sh->envp = ft_free_envp(sh->envp);
		if (sh->path)
			sh->path = ft_free_envp(sh->path);
		sh->hd_path = ft_free(sh->hd_path);
		sh = ft_free(sh);
}

void	ft_run_heredocs(t_token *token, t_shell *sh)
{
	t_iter	s;
	int		pid;
	int		status;
	int		hd_id;
	char	delimiter[4096];
	char	prog_name[256];
	char	file[256];

	hd_id = 1;
	if (!token || !sh)
		return ;
	s = ft_set_iter(0);
	s.cur = token;
	// ft_start_sig_in_this_scope();
	ft_bzero(prog_name, 256);
	ft_strlcpy(prog_name, sh->prog_name, ft_strlen(sh->prog_name));
	while (s.cur)
	{		
		if (s.cur->file)
		{
			ft_bzero(delimiter, 4096);
			ft_bzero(file, 256);
			
			ft_strlcpy(delimiter, s.cur->content, ft_strlen(s.cur->content));
			ft_strlcpy(file, s.cur->file, ft_strlen(s.cur->file));

			pid = fork();
			if (pid == 0)
			{
				ft_free_heredoc(sh);
				ft_sig_default();
				ft_here_doc(prog_name, delimiter, hd_id, file);
				exit (0);
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
					ft_sig_default();
					break ;
				}
			}

		}
		s.cur = s.cur->front;
	}
	ft_sig_default();
}

void	ft_create_and_run_heredocs(t_shell *sh)
{	
	if (sh->nb_heredoc < 1)
		return ;
	ft_run_heredocs(sh->token_lst->first, sh);
}

