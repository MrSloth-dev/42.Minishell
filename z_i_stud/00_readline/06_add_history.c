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
		printf("\n");
		rl_replace_line("", 0); // replace actual text (if exist) with empty str
		rl_on_new_line(); //readline on newline in prompt
		rl_redisplay(); //set defined in readline, again on display
	}
}

void	ft_start_sig()
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

void	ft_readline()
{
	char	*input;

	ft_start_sig();
	input = NULL;
	input = readline("ShellFault$ ");
	if (input && *input)
		add_history(input);
	if (input == NULL)
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
