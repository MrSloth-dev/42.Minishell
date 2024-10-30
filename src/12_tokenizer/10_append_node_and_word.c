/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_append_node_and_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:57:30 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/22 11:44:04 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(void)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->file = NULL;
	new->content = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->left = NULL;
	new->right = NULL;
	new->front = NULL;
	new->back = NULL;
	new->maybe_to_delete = FALSE;
	return (new);
}

int	ft_append_node(t_token_lst *token_lst, char *str, int type, int status)
{
	t_token	*cur;
	t_token	*new_token;

	cur = NULL;
	new_token = ft_new_token();
	if (!new_token)
		return (0);
	new_token->status = status;
	new_token->content = str;
	new_token->type = type;
	new_token->hd_id = -1;
	if (!token_lst->first)
		token_lst->first = new_token;
	else
	{
		cur = token_lst->first;
		while (cur->front)
			cur = cur->front;
		cur->front = new_token;
		new_token->back = cur;
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
		if (len == 0)
			ft_append_node(token_lst, ft_strdup(""), type, status);
		else
			ft_append_node(token_lst, ft_substr(str, 0, len), type, status);
	}
	return (len);
}
