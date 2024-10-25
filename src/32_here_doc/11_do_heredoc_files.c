/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_do_heredoc_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:48:45 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/25 16:57:45 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_make_this_file(t_shell *sh, int hd_id, char *file)
{
	hd_id = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	sh->exit_status = EXIT_SUCCESS;
	close(hd_id);
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
			s.cur->hd_id = sh->nb_heredoc;
			s.cur->file = ft_strjoin_free(ft_strdup(sh->hd_path),
					ft_itoa(sh->nb_heredoc));
			ft_make_this_file(sh, s.cur->hd_id, s.cur->file);
		}
		s.cur = s.cur->front;
	}
}
