#include "minishell.h"

static void	ft_handle_sig(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0); // replace actual text (if exist) with empty str
		rl_on_new_line(); //readline on newline in prompt
		rl_redisplay(); //set defined in readline, again on display
		g_rec_signal = 2;
	}
}

static void	ft_start_sig()
{
	struct sigaction	sa;

	sa.sa_handler = &ft_handle_sig;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL); //handle ctrl + c INSIDE PROGRAM
	signal(SIGQUIT, SIG_IGN); //ignore ctrl + \ OUTSIDE PROGRAM IN REAL TERMINAL, 
	//and program not quit with this combination
}

void	ft_cmd_log(char *line)
{
	char c = '\n';
	int fd = open("cmdlogs", O_RDWR | O_CREAT | O_APPEND);
	write(fd, line, ft_strlen(line));
	write(fd, &c, 1);
	close(fd);
}

t_shell	*ft_readline(t_shell *sh)
{
	char	*pwd;

	pwd = ft_strdup("\033[1;33m");
	pwd = ft_strjoin_free(pwd, ft_strdup(ft_get_env_value("PWD", sh->envp, sh)));
	pwd = ft_strjoin_free(pwd, ft_strdup(":$ "));
	pwd = ft_strjoin_free(pwd, ft_strdup("\033[0m"));
	sh->exit_status = EXIT_SUCCESS;
	ft_start_sig();
	sh->line = NULL;
	sh->line = readline(pwd);
	if ((sh->line && *(sh->line)))
	{
		ft_cmd_log(sh->line); //WARNING :REMOVE
		add_history(sh->line);
	}
	if (g_rec_signal == SIGINT)
		sh->exit_status = 130;
	if (sh->line == NULL || ft_strncmp("exit", sh->line, 4) == 0)
		ft_exit(pwd, sh);
	free(pwd);
	return (sh);
}
