#include "ft_printf.h"
#include "minishell.h"
#include <curses.h>
#include <fcntl.h>

static void	ft_handle_sig(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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

void	ft_here_doc(t_shell *sh, char *delimiter, int hd_id)
{
	char	*line;

	sh->heredoc_fd[hd_id] = open(ft_itoa(hd_id), O_CREAT | O_RDWR | O_APPEND, 0644);
	sh->exit_status = EXIT_SUCCESS;
	ft_start_sig();
	line = NULL;
	line = readline("> ");
	if (sh->line == NULL || ft_strncmp(delimiter, line, 4) == 0)
	{
		close(sh->heredoc_fd[hd_id]);
		ft_exit(NULL, sh);
	}
	else if ((line && *(line)))
	{
		ft_printf(sh->heredoc_fd[hd_id], "%s", line);
		write(sh->heredoc_fd[hd_id], "\n", 1);
	}
}
