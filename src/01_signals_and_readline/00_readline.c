/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:09:31 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 16:08:01 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_sig(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_rec_signal = 2;
	}
}

static void	ft_start_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_handle_sig;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static char	*ft_compress_home(char *path, t_shell *sh)
{
	char	*home;
	char	*compressed;

	compressed = NULL;
	if (!path || !*path)
		return (ft_strdup(""));
	home = ft_get_env_value("HOME", sh->envp, sh);
	if (!home || !*home)
		return (ft_strdup(path));
	if (ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		if (path[ft_strlen(home)] == 0 || path[ft_strlen(home)] == '/')
		{
			compressed = ft_calloc(sizeof(char),
					(ft_strlen(path) - ft_strlen(home) + 2));
			if (!compressed)
				return (ft_strdup(""));
			compressed[0] = '~';
			ft_strlcpy(compressed + 1, path + ft_strlen(home),
				ft_strlen(path) - ft_strlen(home) + 1);
			return (compressed);
		}
	}
	return (ft_strdup(path));
}

static char	*ft_get_prompt(t_shell *sh)
{
	char	*compressed;
	char	*prompt;
	char	*cwd;

	if (!sh || !*sh->envp)
		return (ft_strdup("minishell:"));
	prompt = ft_strdup(YELLOW);
	if (sh->user)
		prompt = ft_strjoin_free(prompt, ft_strdup(sh->user));
	prompt = ft_strjoin_free(prompt, ft_strdup("@"));
	if (sh->hostname)
		prompt = ft_strjoin_free(prompt, ft_strdup(sh->hostname));
	prompt = ft_strjoin_free(prompt, ft_strdup(":"RESET));
	cwd = ft_strdup(ft_get_env_value("PWD", sh->envp, sh));
	if (cwd && *cwd)
	{
		compressed = ft_compress_home(cwd, sh);
		prompt = ft_strjoin_free(prompt, compressed);
	}
	ft_free(cwd);
	prompt = ft_strjoin_free(prompt, ft_strdup("$ "));
	if (!prompt)
		return (ft_free(prompt), ft_free(cwd), NULL);
	return (prompt);
}

t_shell	*ft_readline(t_shell *sh)
{
	char	*prompt;

	prompt = ft_get_prompt(sh);
	if (!prompt || !*prompt)
		prompt = ft_strdup(YELLOW"minishell :$ "RESET);
	ft_start_sig();
	sh->line = NULL;
	sh->line = readline(prompt);
	prompt = ft_free(prompt);
	if ((sh->line && *(sh->line)))
		add_history(sh->line);
	if (g_rec_signal == SIGINT)
		sh->exit_status = 130;
	if (sh->line == NULL || (ft_strcmp(sh->line, "exit") == 0))
		ft_exit(NULL, sh);
	return (sh);
}
