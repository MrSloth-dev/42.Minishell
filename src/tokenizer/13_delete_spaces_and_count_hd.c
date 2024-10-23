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

void	ft_delete_space_and_count_hd(t_token_lst *token_lst, t_shell *sh)
{
	t_iter	s;

	if (!token_lst || !token_lst->first)
		return ;
	s.cur = token_lst->first;
	while (s.cur)
	{
		s.tmp = s.cur;
		s.cur = s.cur->front;
		if (s.tmp->type == WHITE_SPACE || !ft_strcmp(s.tmp->content, "") )
		{
			if (s.cur)
				s.cur->back = s.tmp->back;
			if (s.tmp->back)
				s.tmp->back->front = s.cur;
			free(s.tmp->content);
			free(s.tmp);
			continue ;
		}
		else if (s.tmp->type == HERE_DOC)
		{
			s.tmp->type = REDIR_IN;
			sh->nb_heredoc++;
			s.tmp->hd_id = sh->nb_heredoc;
			s.tmp->file = ft_strjoin_free(sh->hd_path, ft_itoa(sh->nb_heredoc));
			//ft_make_hd_file(sh, s.tmp->hd_id, s.tmp->file);
		}
	}
}
