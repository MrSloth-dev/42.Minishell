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

#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

void	ft_update_shlvl(int value, char **envp)
{
	char	*value_str;
	char	*key;
	int		i;

	value_str = ft_itoa(value);
	i = 0;
	while (envp && envp[i])
	{
		key = ft_get_env_key(envp[i]);
		if (ft_strcmp("SHLVL", key) == 0)
		{
			ft_free(envp[i]);
			envp[i] = ft_strdup("SHLVL=");
			envp[i] = ft_strjoin_free(envp[i], value_str);
			key = ft_free(key);
			return ;
		}
		key = ft_free(key);
		i++;
	}
	value_str = ft_free(value_str);
}

void	ft_handle_shlvl(char **envp, t_shell *sh)
{
	int		shlvl_value;
	char	*shlvl_str;

	shlvl_str = ft_get_env_value("SHLVL", envp, sh);
	if (!shlvl_str || !*shlvl_str)
		shlvl_value = 0;
	else
		shlvl_value = ft_atoi(shlvl_str);
	if (!*ft_get_env_value("SHLVL", envp, sh) || shlvl_value == 0)
		ft_update_shlvl(1, sh->envp);
	else if (shlvl_value == 999)
	{
		ft_printf(STDERR_FILENO,
			"%s: warning: shell level (1000) too high, resetting to 1");
		ft_update_shlvl(1, sh->envp);
	}
	else
		ft_update_shlvl(shlvl_value + 1, sh->envp);
}

char	*ft_get_hostname(void)
{
	char	*hostname;
	int		fd;
	int		size_read;

	fd = open("/etc/hostname", O_RDONLY);
	hostname = malloc(sizeof(char) * 256);
	if (!hostname)
		return (close(fd), NULL);
	if (fd == -1)
		return (ft_free(hostname), NULL);
	size_read = read(fd, hostname, 255);
	close(fd);
	if (size_read > 0)
		return (hostname[size_read - 1] = 0, hostname);
	free(hostname);
	return (ft_strdup("localhost"));
}

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
	// ft_handle_shlvl(sh->envp, sh);
	sh->hostname = ft_get_hostname();
	sh->user = getenv("USER");
	sh->path = NULL;
	sh->hd_path = ft_strjoin_free(getcwd(NULL, 0), ft_strdup("/.tmp/"));
	sh->nb_heredoc = 0;
	sh->exit_status = EXIT_SUCCESS;
	// SET DEFAULT VARS TO ENV? env -i bash
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