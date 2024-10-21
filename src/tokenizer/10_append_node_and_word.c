/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_append_node_and_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:57:30 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/21 10:58:57 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append_node(t_token_lst *token_lst, char *str, int type, int status)
{
	t_token	*cur;
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	if (!new_token)
		return (0);
	new_token->status = status;
	new_token->content = str;
	new_token->type = type;
	new_token->next = NULL;
	new_token->hd_id = -1;
	if (!token_lst->first)
	{
		token_lst->first = new_token;
		new_token->prev = NULL;
	}
	else if (token_lst->first)
	{
		cur = token_lst->first;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
		new_token->prev = cur;
	}
	return (ft_strlen(str));
}

int	ft_append_word(t_token_lst *token_lst, char *str, int type, int status)
{
	int	len;

	len = 0;
	if (status == NORMAL)
	{
		while (str[len] && ft_is_word(str[len]) == TRUE)
			len++;
		ft_append_node(token_lst, ft_substr(str, 0, len), type, status);
	}
	return (len);
}
