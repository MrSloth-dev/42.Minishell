/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_append_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:53:18 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/21 11:05:10 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_append_redir_in(t_token_lst *token_lst, t_iter *h)
{
	if (h->line[h->i + 1] && h->line[h->i + 1] == '<')
	{
		h->i += ft_how_much_consecutives_spaces(h->line + h->i + 2) + 2;
		h->i += ft_append_word(token_lst, h->line + h->i, HERE_DOC, h->status);
	}
	else
	{
		h->i += ft_how_much_consecutives_spaces(h->line + h->i + 1) + 1;
		h->i += ft_append_word(token_lst, h->line + h->i, REDIR_IN, h->status);
	}
}

static void	ft_append_redir_out(t_token_lst *token_lst, t_iter *h)
{
	if (h->line[h->i + 1] && h->line[h->i + 1] == '>')
	{
		h->i += ft_how_much_consecutives_spaces(h->line + h->i + 2) + 2;
		h->i += ft_append_word(token_lst, h->line + h->i,
				DBLE_REDIR_OUT, h->status);
	}
	else
	{
		h->i += ft_how_much_consecutives_spaces(h->line + h->i + 1) + 1;
		h->i += ft_append_word(token_lst, h->line + h->i, REDIR_OUT, h->status);
	}
}

int	ft_append_redir(t_token_lst *token_lst, char *line, int status)
{
	t_iter	h;

	if (!line || !token_lst)
		return (0);
	h = ft_set_iter(0);
	h.line = line;
	h.c = line[0];
	h.status = status;
	if (h.c == '<')
		ft_append_redir_in(token_lst, &h);
	else if (h.c == '>')
		ft_append_redir_out(token_lst, &h);
	return (h.i);
}
