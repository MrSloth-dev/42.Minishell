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
		if (s.tmp->type == WHITE_SPACE)
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
			s.tmp->hd_id = sh->nb_heredoc;
			sh->nb_heredoc++;
		}
	}
}
