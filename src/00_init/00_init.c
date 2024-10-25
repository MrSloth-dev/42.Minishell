/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:35:17 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/24 14:35:26 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*ft_init_shell(char *envp[], char *argv_zero)
{
	t_shell	*sh;

	sh = ft_calloc(1, sizeof(t_shell));
	if (!sh)
	{
		printf("Error allocating \"*sh\" struct!\n");
		return (NULL);
	}
	sh->pid = ft_getpid(sh);
	sh->prog_name = argv_zero + 2;
	sh->token_lst = NULL;
	sh->envp = ft_copy_envp(envp, 0);
	sh->path = NULL;
	sh->hd_path = ft_strjoin_free(getcwd(NULL, 0), ft_strdup("/.tmp/"));
	sh->nb_heredoc = 0;
	sh->exit_status = EXIT_SUCCESS;
	return (sh);
}

char	**ft_copy_envp(char **envp, int extra)
{
	char	**temp_envp;
	int		i;

	i = 0;
	while (envp && envp[i])
		i++;
	temp_envp = ft_calloc(sizeof(char *), i + extra + 1);
	if (!temp_envp)
		return (NULL);
	i = -1;
	while (envp && envp[++i])
		temp_envp[i] = ft_strdup(envp[i]);
	while (extra-- > 0)
		temp_envp[i++] = 0;
	return (temp_envp);
}
	// temp_envp[i] = 0;
