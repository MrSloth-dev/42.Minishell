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

#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h>

static void	ft_handle_sig(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
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

char	*ft_compress_home(char *path, t_shell *sh)
{
	char	*home;
	char	*compressed;

	compressed = NULL;
	home = ft_get_env_value("HOME", sh->envp, sh);
	if (!*home | !*path)
		return (ft_strdup(""));
	if (ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		if (path[ft_strlen(home)] == 0 || path[ft_strlen(home)] == '/')
		{
			compressed = malloc(sizeof(char) *(ft_strlen(path) - ft_strlen(home) + 2));
			if (!compressed)
				return (NULL);
			compressed[0] = '~';
			ft_strlcpy(compressed + 1, path + ft_strlen(home), ft_strlen(path) - ft_strlen(home) + 1);
			return (compressed);
		}
	}
	return (ft_strdup(path));
}

char	*ft_get_prompt(t_shell *sh)
{
	char	*prompt;
	char	*cwd;

	ft_printf(STDOUT_FILENO, RED);
	cwd = ft_get_env_value("PWD", sh->envp, sh);
	prompt = ft_get_env_value("USER", sh->envp, sh);
	if (!prompt | !cwd)
		return (NULL);
	prompt = ft_strjoin(prompt, RESET"@"YELLOW);
	if (!prompt || !*ft_get_env_value("SESSION_MANAGER", sh->envp, sh))
		return (NULL);
	prompt = ft_strjoin_free(prompt,
			ft_strdup(ft_get_env_value("SESSION_MANAGER", sh->envp, sh) + 6));
	if (!prompt)
		return (NULL);
	*strchr(prompt, '.') = 0;
	prompt = ft_strjoin_free(prompt, ft_strdup(RESET":"GREEN));
	if (!prompt)
		return (NULL);
	if (cwd)
		prompt = ft_strjoin_free(prompt, ft_compress_home(cwd, sh));
	prompt = ft_strjoin_free(prompt, ft_strdup("$ "RESET));
	if (!prompt)
		return (NULL);
	return (prompt);
}

// char	*ft_get_prompt(t_shell *sh)
// {
// 	char	*pwd;
// 	char	*cur_pwd;
//
// 	cur_pwd = ft_get_env_value("PWD", sh->envp, sh);
// 	if (!cur_pwd[0])
// 		return (free(cur_pwd), NULL);
// 	pwd = ft_strdup("\033[1;33m");
// 	pwd = ft_strjoin_free(pwd, ft_strdup(cur_pwd));
// 	pwd = ft_strjoin_free(pwd, ft_strdup(":$ "));
// 	pwd = ft_strjoin_free(pwd, ft_strdup("\033[0m"));
// 	return (pwd);
// }

t_shell	*ft_readline(t_shell *sh)
{
	char	*prompt;

	prompt = ft_get_prompt(sh);
	if (!prompt)
		prompt = ft_strdup(YELLOW"minishell :$ "RESET);
	ft_start_sig();
	sh->line = NULL;
	sh->line = readline(prompt);
	if ((sh->line && *(sh->line)))
		add_history(sh->line);
	if (g_rec_signal == SIGINT)
		sh->exit_status = 130;
	if (sh->line == NULL || (ft_strcmp(sh->line, "exit") == 0))
	{
		prompt = ft_free(prompt);
		ft_exit(NULL, sh);
	}
	prompt = ft_free(prompt);
	return (sh);
}
