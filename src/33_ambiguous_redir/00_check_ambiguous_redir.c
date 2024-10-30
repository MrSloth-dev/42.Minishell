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
	while (token)
	{
		if (token->type > HERE_DOC && ft_strlen(token->content) == 0)
		{
			sh->exit_status = 1;
			token->type = WORD;
			ft_printf(1, "%s: ambiguous redirect\n", sh->prog_name);
		}
		token = token->front;
	}
}
