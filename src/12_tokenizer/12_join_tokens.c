/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_join_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:43:24 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/21 16:57:10 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_join_to_next_token(t_token *cur, t_token *to_join)
{
	char	*str_to_free;

	if (!cur || !to_join)
		return ;
	str_to_free = cur->content;
	cur->content = ft_strjoin(cur->content, to_join->content);
	cur->front = to_join->front;
	if (cur->front)
		cur->front->back = cur;
	to_join->content = ft_free(to_join->content);
	to_join = ft_free(to_join);
	str_to_free = ft_free(str_to_free);
}

void	ft_join_tokens(t_token_lst *token_lst)
{
	t_token	*cur;

	if (!token_lst && !token_lst->first)
		return ;
	cur = token_lst->first;
	while (cur)
	{
		if (cur->type == WORD || cur->type == HERE_DOC)
		{
			while (cur->front && (cur->front->type == WORD))
				ft_join_to_next_token(cur, cur->front);
		}
		else if (cur->type > HERE_DOC)
		{
			while (cur->front && cur->front->type == WORD)
				ft_join_to_next_token(cur, cur->front);
		}
		cur = cur->front;
	}
}
