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

void	ft_free_inside_heredoc(t_shell *sh)
{
	if (!sh)
		return ;
	sh->line = ft_free(sh->line);
	ft_free_tokens(sh);
	sh->token_lst = ft_free(sh->token_lst);
	if (sh->envp)
		sh->envp = ft_free_envp(sh->envp);
	if (sh->path)
		sh->path = ft_free_envp(sh->path);
	sh->hd_path = ft_free(sh->hd_path);
	sh->hostname = ft_free(sh->hostname);
	sh = ft_free(sh);
}

void	ft_get_file_name(char hd_file[4096], char *src_file)
{
	int		len;

	len = 0;
	ft_bzero(hd_file, 4096);
	len = ft_strlen(src_file) + 1;
	if (len >= 4095)
		len = 4094;
	ft_strlcpy(hd_file, src_file, len);
}

void	ft_get_delimiter(char delimiter[4096], char *content)
{
	int	len;

	len = 0;
	ft_bzero(delimiter, 4096);
	len = ft_strlen(content) + 1;
	if (len >= 4095)
		len = 4094;
	ft_strlcpy(delimiter, content, len);
}
