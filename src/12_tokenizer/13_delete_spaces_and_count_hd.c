/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_delete_spaces_and_count_hd.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:52:03 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/21 16:58:00 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_make_hd_file(t_shell *sh, int hd_id, char *file)
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
	s = ft_set_iter(0);
	s.cur = token;
	sh->nb_heredoc = 0;
	while (s.cur)
	{
		if (s.cur->type == HERE_DOC)
		{
			//s.tmp->type = REDIR_IN;
			sh->nb_heredoc++;
			s.cur->file = ft_strjoin_free(ft_strdup(sh->hd_path), ft_itoa(sh->nb_heredoc));
		}
		s.cur = s.cur->front;
	}
	if (sh->nb_heredoc > 0)
	{
		s.cur = token;
		ft_make_heredoc_fd(sh->nb_heredoc, sh);
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

void	ft_delete_spaces(t_token_lst *token_lst, t_shell *sh)
{
	t_iter	s;

	if (!token_lst || !token_lst->first)
		return ;
	s.cur = token_lst->first;
	while (s.cur && sh)
	{
		s.tmp = s.cur;
		s.cur = s.cur->front;
		if (s.tmp->type == WHITE_SPACE || !ft_strcmp(s.tmp->content, "") )
		{
			if (s.cur)
				s.cur->back = s.tmp->back;
			if (s.tmp->back)
				s.tmp->back->front = s.cur;
			s.tmp->content = ft_free(s.tmp->content);
			s.tmp = ft_free(s.tmp);
		}
	}
}


