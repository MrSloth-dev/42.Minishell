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
	char	pwd[1];
	char	*line;

	sh->heredoc_fd[hd_id] = open(ft_itoa(hd_id), O_CREAT | O_APPEND, 0644);
	pwd[0] = '>';
	sh->exit_status = EXIT_SUCCESS;
	ft_start_sig();
	line = NULL;
	line = readline(pwd);
	if ((line && *(line)))
		write(sh->heredoc_fd[hd_id], &line, ft_strlen(line));
	if (ft_strncmp(delimiter, line, 4) == 0)
	{
		close(sh->heredoc_fd[hd_id]);
		ft_exit(pwd, sh);
	}
}
