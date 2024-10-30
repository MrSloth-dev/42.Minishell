/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_check_ambiguous_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:12:15 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/29 08:14:41 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_ambiguous_redir(t_token *token, t_shell *sh)
{
	if (!token || !sh)
		return ;
	sh->ambig_redir = 0;
	while (token)
	{
		if (token->type > HERE_DOC && ft_strlen(token->content) == 0)
		{
			token->type = WORD;
			sh->ambig_redir++;
		}
		token = token->front;
	}
}
// we need to classify ths node as WORD, to join empty tokens in other functions

void	ft_print_ambiguous_redir_msg(t_shell *sh)
{
	if (!sh || sh->ambig_redir == 0)
		return ;
	while (sh->ambig_redir-- > 0)
	{
		ft_printf(1, "%s: ambiguous redirect\n", sh->prog_name);
	}
	sh->exit_status = 1;
	if (sh->head && sh->head->type == ND_EXEC)
		sh->head = NULL;
}
// last if is for preventing execution, if there is ambiguous redir.
// if have a ND_PIPE in sh->head, the execution must continue
