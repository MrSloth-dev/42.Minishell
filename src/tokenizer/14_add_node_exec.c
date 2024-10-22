/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_add_node_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:01:01 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/22 13:02:13 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_node_exec(t_token_lst *token_lst, t_shell *sh)
{
	t_iter	h;
	t_token	*exec_node;

	if (!token_lst || !token_lst->first || !sh)
		return ;
	h = ft_set_iter(0);
	h.cur = token_lst->first->front;
	while (h.cur)
	{
		h.tmp = h.cur;
		h.cur = h.cur->front;
		if (h.tmp->type == ND_PIPE && h.cur)
		{
			exec_node = ft_new_token();
			if (!exec_node)
				return ;
			exec_node->type = ND_EXEC;
			exec_node->content = ft_strdup("ND_EXEC ");
			h.cur->back = exec_node;
			exec_node->front = h.cur;
			h.tmp->front = exec_node;
			exec_node->back = h.tmp;
		}
	}
}
