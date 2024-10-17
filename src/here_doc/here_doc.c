#include "ft_printf.h"
#include "minishell.h"
#include <curses.h>
#include <fcntl.h>

// static void	ft_handle_sig(int signal)
// {
// 	if (signal == SIGINT)
// 	{
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
// 	sa.sa_handler = &ft_handle_sig;
// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	sigaddset(&sa.sa_mask, SIGINT);
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	ft_here_doc(t_shell *sh, char *delimiter, int hd_id, char *file)
{
	char	*line;

	sh->heredoc_fd[hd_id] = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	sh->exit_status = EXIT_SUCCESS;
//	ft_start_sig_in_this_scope();
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (sh->line == NULL || ft_strcmp(delimiter, line) == 0)
		{
			close(sh->heredoc_fd[hd_id]);
			//ft_exit(NULL, sh);
			break ;
		}
		else if ((line && *(line)))
		{
			ft_printf(sh->heredoc_fd[hd_id], "%s", line);
			write(sh->heredoc_fd[hd_id], "\n", 1);
		}
	}
}

void	ft_run_heredocs(t_token *token, t_shell *sh)
{
	t_iter	s;
	char	*file;
	char	*tmp;

	if (!token || !sh)
		return ;
	s = set_iter(0);
	s.cur = token;
	if (s.cur && s.cur->type != ND_PIPE && s.cur->right)
	{
		s.cur = s.cur->right;
		while (s.cur)
		{
			if (s.cur->type == HERE_DOC)
			{
				s.cur->type = REDIR_IN;
				file = ft_itoa(s.cur->hd_id);
				ft_here_doc(sh, s.cur->content, s.cur->hd_id, file);
				tmp = s.cur->content;
				s.cur->content = file;
				free(tmp);
			}
			s.cur = s.cur->next;
		}
	}
	else if (s.cur)
	{
		ft_run_heredocs(s.cur->left, sh);
		ft_run_heredocs(s.cur->right, sh);
	}
}

void	ft_create_and_run_heredocs(t_shell *sh)
{
	ft_make_heredoc_fd(sh->nb_heredoc, sh);
	ft_run_heredocs(sh->token_lst->first, sh);

}

