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

static void	ft_update_shlvl(int value, char **envp)
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

static void	ft_handle_shlvl(char **envp, t_shell *sh)
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
	else if (shlvl_value > 0)
		ft_update_shlvl(0, sh->envp);
	else if (shlvl_value == 999)
	{
		ft_printf(STDERR_FILENO,
			"%s: warning: shell level (1000) too high, resetting to 1");
		ft_update_shlvl(1, sh->envp);
	}
	else
		ft_update_shlvl(shlvl_value + 1, sh->envp);
}

static char	*ft_get_hostname(void)
{
	char	*hostname;
	int		fd;
	int		size_read;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (close(fd), ft_strdup("localhost"));
	hostname = ft_calloc(sizeof(char), 256);
	if (!hostname)
		return (close(fd), ft_free(hostname), ft_strdup("localhost"));
	size_read = read(fd, hostname, 255);
	close(fd);
	if (size_read > 0)
		return (hostname[size_read - 1] = 0, hostname);
	free(hostname);
	return (ft_strdup("localhost"));
}

t_shell	*ft_init_shell(char *envp[], int ac, char *av[], t_shell *sh)
{
	if (ac != 1)
	{
		ft_printf(STDERR_FILENO, "%s: %s: No such file or directory\n",
			av[0] + 2, av[1]);
		exit (127);
	}
	sh = ft_calloc(1, sizeof(t_shell));
	if (!sh)
	{
		ft_printf(STDERR_FILENO, "Error allocating \"*sh\" struct!\n");
		return (NULL);
	}
	sh->pid = ft_getpid(sh);
	sh->prog_name = av[0] + 2;
	sh->token_lst = NULL;
	sh->envp = ft_copy_envp(envp, 0);
	ft_handle_shlvl(sh->envp, sh);
	sh->hostname = ft_get_hostname();
	sh->user = getenv("USER");
	sh->path = NULL;
	sh->hd_path = ft_strdup("/tmp/");
	sh->nb_heredoc = 0;
	sh->ambig_redir = 0;
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
