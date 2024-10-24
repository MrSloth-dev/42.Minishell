/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:13:39 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/22 16:30:21 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_and_exit(t_token *token, t_shell *sh, int exit_flag)
{
	int	exit_status;

	(void)token;
	exit_status = sh->exit_status;
	if (!sh)
		return ;
	sh->line = ft_free(sh->line);
	ft_free_lst_shell(sh);
	sh->token_lst = ft_free(sh->token_lst);



	if (exit_flag == TRUE)
	{
		if (sh->envp)
			sh->envp = ft_free_envp(sh->envp);
		if (sh->path)
			sh->path = ft_free_envp(sh->path);
		sh->hd_path = ft_free(sh->hd_path);
		sh = ft_free(sh);
		exit (exit_status);
	}

	sh = ft_free(sh);
}

void	ft_free_lst_shell(t_shell *sh)
{
	t_token	*cur;
	t_token	*tmp;

	sh->head = NULL;
	if (sh->token_lst && sh->token_lst->first)
	{
		cur = sh->token_lst->first;
		while (cur)
		{
			tmp = cur;
			cur = cur->front;
			tmp->file = ft_free(tmp->file);
			tmp->content = ft_free(tmp->content);
			tmp = ft_free(tmp);
		}
	}
	ft_clean_hd_array(sh);
	sh->token_lst = ft_free(sh->token_lst);
}

void	*ft_free_envp(char	**envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	envp = ft_free(envp);
	return (NULL);
}

void	ft_clean_hd_files(t_shell *sh)
{
	t_token	*cur;

	if (!sh || !sh->token_lst || !sh->token_lst->first)
		return ;
	cur = sh->token_lst->first;
	while (cur)
	{
		if (cur->file)
		{
			unlink(cur->file);
		}
		cur = cur->front;
	}
}

void	ft_clean_hd_array(t_shell *sh)
{
	if (sh->nb_heredoc > 0)
		sh->heredoc_fd = ft_free(sh->heredoc_fd);
}
