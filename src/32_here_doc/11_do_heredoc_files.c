#include "minishell.h"

static void	ft_make_hd_file(t_shell *sh, int hd_id, char *file)
{
	sh->heredoc_fd[hd_id] = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	sh->exit_status = EXIT_SUCCESS;
	close(sh->heredoc_fd[hd_id]);
}

void	ft_do_heredoc_files(t_token *token, t_shell *sh)
{
	t_iter	s;

	if (!token || !sh)
		return ;
	sh->nb_heredoc = 0;
	s = ft_set_iter(0);
	s.cur = token;
	while (s.cur)
	{
		if (s.cur->type == HERE_DOC)
		{
			sh->nb_heredoc++;
			s.cur->file = ft_strjoin_free(ft_strdup(sh->hd_path),
					ft_itoa(sh->nb_heredoc));
		}
		s.cur = s.cur->front;
	}
	if (sh->nb_heredoc > 0)
	{
		s.cur = token;
		ft_make_heredoc_fd_array(sh->nb_heredoc, sh);
		while (s.cur)
		{
			if (s.cur->file)
			{
				s.cur->hd_id = ++s.i;
				ft_make_hd_file(sh, s.cur->hd_id, s.cur->file);
			}
			s.cur = s.cur->front;
		}
	}
}
