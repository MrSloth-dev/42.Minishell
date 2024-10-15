#include "ft_printf.h"
#include "minishell.h"

static void	ft_handle_sig(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0); // replace actual text (if exist) with empty str
		rl_on_new_line(); //readline on newline in prompt
		rl_redisplay(); //set defined in readline, again on display
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
		add_history(sh->line);
	if (sh->line == NULL || ft_strncmp("exit", sh->line, 4) == 0)
		ft_exit(pwd, sh);
	free(pwd);
	return (sh);
}
