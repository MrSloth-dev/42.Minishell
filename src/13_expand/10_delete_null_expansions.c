/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_delete_null_expansions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:45:28 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/30 10:48:09 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_delete_this_null_expansion(t_iter *s)
{
	if (!s || !s->tmp)
		return ;
	if (s->tmp->back)
		s->tmp->back->front = s->cur;
	s->tmp->content = ft_free(s->tmp->content);
	s->tmp = ft_free(s->tmp);
}

void	ft_delete_null_expansions_if_needed(t_shell *sh)
{
	t_iter	s;
	int		is_to_delete;

	if (!sh || !sh->token_lst || !sh->token_lst->first)
		return ;
	s.cur = sh->token_lst->first;
	while (s.cur && sh)
	{
		is_to_delete = FALSE;
		s.tmp = s.cur;
		s.cur = s.cur->front;
		if (s.tmp->maybe_to_delete == TRUE)
		{
			if (s.cur && s.cur->type != WORD)
			{
				is_to_delete = TRUE;
				s.cur->back = s.tmp->back;
			}
			else if (!s.cur && s.tmp->back && s.tmp->back->type == ND_EXEC)
				is_to_delete = TRUE;
			if (is_to_delete == TRUE)
				ft_delete_this_null_expansion(&s);
		}
	}
}
