/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_convert_empty_strings.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:51:45 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/30 10:52:39 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_convert_empty_strings(t_token *token)
{
	t_token	*cur;

	if (!token)
		return ;
	cur = token;
	while (cur)
	{
		if (cur->type == WORD && cur->content
			&& *cur->content == '\x02'
			&& cur->back && cur->back->type != ND_EXEC)
		{
			*cur->content = 0;
		}
		cur = cur->front;
	}
}
