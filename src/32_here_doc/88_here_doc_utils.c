/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   88_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:14:03 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/24 14:38:57 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_make_heredoc_fd_array(int nb_heredoc, t_shell *sh)
{
	sh->heredoc_fd = ft_calloc(sizeof(int), nb_heredoc + 1);
	if (!sh->heredoc_fd)
	{
		ft_free_lst_shell(sh);
		return ;
	}
	sh->heredoc_fd[nb_heredoc] = -1;
}
