#include "ft_printf.h"
#include "minishell.h"
#include <curses.h>
#include <fcntl.h>
#include <sys/wait.h>



void	ft_here_doc(char *prog_name, char *delimiter, int hd_id, char *file)
{
	char	*line;
	line = NULL;
	while (1)
	{
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

void	ft_free_inside_heredoc(t_shell *sh)
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
	ft_bzero(prog_name, 256);
	ft_strlcpy(prog_name, sh->prog_name, ft_strlen(sh->prog_name) + 1);
	while (s.cur)
	{		
		if (s.cur->file)
		{

			ft_bzero(delimiter, 4096);
			ft_bzero(file, 256);
			ft_strlcpy(delimiter, s.cur->content, ft_strlen(s.cur->content) + 1);
			ft_strlcpy(file, s.cur->file, ft_strlen(s.cur->file) + 1);

			pid = fork();
			if (pid == 0)
			{
				ft_sig_child();
				ft_free_inside_heredoc(sh);
				ft_here_doc(prog_name, delimiter, hd_id, file);
				exit (0);
			}
			else
			{
				ft_sig_mute();
				waitpid(pid, &status, 0);
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				{
					ft_printf(1, "\n");
					sh->head = NULL;
					sh->exit_status = 130;
					ft_sig_restore();
					break ;
				}
			}
		}
		s.cur = s.cur->front;
	}
	ft_sig_restore();
}

void	ft_create_and_run_heredocs(t_shell *sh)
{	
	if (sh->nb_heredoc < 1)
		return ;
	ft_run_heredocs(sh->token_lst->first, sh);
}

