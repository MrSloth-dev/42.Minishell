// #include "study.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	ft_handle_sig(int signal)
{
	if (signal == SIGINT)
	{
		//rl_replace_line("", 0);
		rl_on_new_line(); //readline on newline in prompt
		printf("\n");
		rl_redisplay();
	}
}

void	ft_start_sig()
{
	struct sigaction	sa;

	sa.sa_handler = &ft_handle_sig;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL); //handle ctrl + c in program
	signal(SIGQUIT, SIG_IGN); //ignore ctrl + c to exit in real terminal
}

void	ft_readline()
{
	char	*str;

	ft_start_sig();
	str = NULL;
	str = readline("ShellFault-> ");
	if (str == NULL)
	{
		printf("exit\n");
		exit (EXIT_SUCCESS);
	}
}

int	main(void)
{
	while (1)
	{
		ft_readline();
	}
}

// needs -lreadline in compilation
// in execution with valgrind, use
// valgrind --suppressions=s.supp ./a.out
