/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_split_this_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:18:56 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/30 15:20:28 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_this_node(t_iter *out)
{
	t_iter	in;

	in = ft_set_iter(0);
	if (!out || !out->cur || !out->cur->content)
		return ;

	in.split = ft_split(out->cur->content, 32);
	if (!in.split)
		return ;

	in.front = out->cur->front;
	in.back = out->cur->back;

	in.new_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!in.new_lst)
	{
		ft_free_envp(in.split);
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
