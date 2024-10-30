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

static int	ft_set_backup_nodes_and_alloc_lst(t_iter *in, t_iter *out)
{
	in->split = ft_split(out->cur->content, 32);
	if (!in->split)
		return (FALSE);
	in->front = out->cur->front;
	in->back = out->cur->back;
	in->new_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!in->new_lst)
	{
		ft_free_envp(in->split);
		return (FALSE);
	}
	while (in->split[in->i] != NULL)
		in->i++;
	if (in->i == 0)
	{
		ft_free_envp(in->split);
		ft_free(in->new_lst);
		return (FALSE);
	}
	return (TRUE);
}

static int	ft_create_new_lst_to_link(t_iter *in)
{
	in->j = 0;
	in->k = 0;
	while (in->split[in->k])
	{
		if ((in->j % 2) == 0)
			ft_append_node(in->new_lst, in->split[in->k++], WORD, NORMAL);
		else
			ft_append_node(in->new_lst, ft_strdup(" "), WHITE_SPACE, NORMAL);
		in->j++;
	}
	if (!in->new_lst->first)
		return (FALSE);
	return (TRUE);
}

static void	ft_clean_out_node_and_link_to_new(t_iter *in, t_iter *out)
{
	out->cur->content = ft_free(out->cur->content);
	out->cur = ft_free(out->cur);
	out->cur = in->new_lst->first;
}

static void	ft_only_free_here(t_iter *in)
{
	ft_free(in->new_lst);
	ft_free(in->split);
}

void	ft_split_this_node(t_iter *out)
{
	t_iter	in;

	if (!out || !out->cur || !out->cur->content)
		return ;
	in = ft_set_iter(0);
	if (ft_set_backup_nodes_and_alloc_lst(&in, out) == FALSE)
		return ;
	if (ft_create_new_lst_to_link(&in) == FALSE)
	{
		ft_only_free_here(&in);
		return ;
	}
	ft_clean_out_node_and_link_to_new(&in, out);
	in.cur_right = out->cur;
	while (in.cur_right->front)
		in.cur_right = in.cur_right->front;
	out->cur->back = in.back;
	if (in.back)
		in.back->front = out->cur;
	in.cur_right->front = in.front;
	if (in.front)
		in.front->back = in.cur_right;
	while (out->cur != in.cur_right)
		out->cur = out->cur->front;
	ft_only_free_here(&in);
}
