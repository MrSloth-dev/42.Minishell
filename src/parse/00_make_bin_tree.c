/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_make_bin_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:41:05 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/22 11:41:09 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_make_left_lst(t_iter *s, t_token *token)
{
	if (!token->left)
	{
		token->left = s->cur;
		s->cur_left = s->cur;
	}
	else
	{
		s->cur->prev = s->cur_left;
		s->cur->prev->next = s->cur;
		s->cur_left = s->cur_left->next;
	}
}

static void	ft_make_right_lst(t_iter *s, t_token *token)
{
	if (!token->right)
	{
		token->right = s->cur;
		s->cur_right = s->cur;
	}
	else
	{
		s->cur->prev = s->cur_right;
		s->cur->prev->next = s->cur;
		s->cur_right = s->cur_right->next;
	}
}

t_token	*ft_make_bin_tree(t_token *token)
{
	t_iter	s;

	if (!token || !token->front)
		return (NULL);
	s = ft_set_iter(0);
	s.cur = token->front;
	while (s.cur && s.cur->type != ND_PIPE && token)
	{
		if (s.cur->type == WORD && s.cur->type != ND_EXEC)
			ft_make_left_lst(&s, token);
		else if (s.cur->type != ND_EXEC)
			ft_make_right_lst(&s, token);
		s.cur = s.cur->front;
	}
	if (s.cur && s.cur->type == ND_PIPE)
	{
		s.cur->left = token;
		s.cur->right = ft_make_bin_tree(s.cur->front);
		token = s.cur;
	}
	return (token);
}
