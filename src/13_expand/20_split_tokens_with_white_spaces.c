/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_split_tokens_with_white_spaces.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:41:00 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/30 14:42:50 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_need_to_split_spaces(char *str)
{
	int	i;
	int	have_spaces;

	i = 0;
	have_spaces = FALSE;
	while (str[i])
	{
		if (ft_is_space(str[i]) == TRUE && str[i + 1])
			have_spaces = TRUE;
		if (have_spaces == TRUE)
		{
			i--;
			while (str[++i])
				if (ft_is_space(str[i]) == TRUE)
					str[i] = 32;
			if (i > 0 && !str[i] && str[i - 1] == 32)
				str[i - 1] = '\t';
			i--;
		}
		i++;
	}
	return (have_spaces);
}

void	ft_split_this_node(t_iter *out)
{
	t_iter	in;

	in = ft_set_iter(0);
	if (!out || !out->cur || !out->cur->content)
		return ;
	in.new_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!in.new_lst)
		return ;
	in.front = out->cur->front;
	in.back = out->cur->back;
	in.split = ft_split(out->cur->content, 32);
	if (!in.split)
	{
		ft_free(in.new_lst);
		return ;
	}
	while (in.split[in.i] != NULL)
		in.i++;
	if (in.i == 0)
	{
		ft_free_envp(in.split);
		ft_free(in.new_lst);
		return ;
	}
	in.i++;
	while (in.i > 0)
	{
		if (in.i % 2 == 1)
			ft_append_node(in.new_lst, in.split[in.j++], WORD, NORMAL);
		else
			ft_append_node(in.new_lst, ft_strdup(" "), WHITE_SPACE, NORMAL);
		in.i--;
	}

	out->cur->content = ft_free(out->cur->content);
	out->cur = ft_free(out->cur);
	out->cur = in.new_lst->first;
	
	in.cur_right = out->cur;
	while (in.cur_right->front)
		in.cur_right = in.cur_right->front; //

	out->cur->back = in.back;
	if (in.back)
		in.back->front = out->cur;

	in.cur_right->front = in.front;
	if (in.front)
		in.front->back = in.cur_right;

	while (out->cur != in.cur_right)
		out->cur = out->cur->front;

	ft_free(in.new_lst);
	ft_free(in.split);
}

void	ft_split_tokens_with_white_spaces(t_shell *sh)
{
	t_iter	s;
	int		need_to_split;

	if (!sh || !sh->token_lst || !sh->token_lst->first)
		return;
	s.cur = sh->token_lst->first;
	while (s.cur)
	{
		need_to_split = FALSE;
		if (s.cur->type == WORD && s.cur->status == NORMAL)
			need_to_split = ft_check_if_need_to_split_spaces(s.cur->content);
		if (need_to_split == TRUE)
			ft_split_this_node(&s);
		s.cur = s.cur->front;
	}

}
