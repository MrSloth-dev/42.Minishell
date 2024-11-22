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

static int	ft_check_if_need_to_split_spaces(char *str)
{
	int	i;
	int	have_spaces;

	i = 0;
	have_spaces = FALSE;
	if (ft_strlen(str) <= 1)
		return (have_spaces);
	while (str[i])
	{
		if (ft_is_space(str[i]) == TRUE)
		{
			have_spaces = TRUE;
			str[i] = 32;
		}
		i++;
	}
	return (have_spaces);
}

void	ft_split_tokens_with_white_spaces(t_shell *sh)
{
	t_iter	s;
	int		need_to_split;

	if (!sh || !sh->token_lst || !sh->token_lst->first)
		return ;
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
