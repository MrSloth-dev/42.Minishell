static void	send_kills(int server_pid, char *str)
{
	int		bit;
	char	byte;

	bit = 8;
	ft_printf("Server PID: %d\n", server_pid);
	while (*str)
	{
		bit = 8;
		byte = *str++;
		while (bit--)
		{
			if (byte >> bit & 1)
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			pause();
		}
	}
	bit = 8;
	while (bit--)
	{
		kill(server_pid, SIGUSR1);
		pause();
	}
}

static void	client_handle(int signal, siginfo_t *sig, void *a)
{
	static unsigned int	n_bits = 0;

	(void)sig;
	(void)a;
	if (signal == SIGUSR2)
		n_bits++;
	else if (signal == SIGUSR1)
	{
		n_bits++;
		ft_printf("Server received %d bytes! %s\n", n_bits / 8, EMOJI_3);
		exit (0);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	s;
	int					client_pid;

	if (ac != 3 || ft_strlen(av[1]) == 0)
	{
		ft_printf("Please check your ARG's!\n");
		ft_printf("Usage: ./client server_pid text\n");
		return (1);
	}
	client_pid = getpid();
	ft_printf("\nBytes to send: %d bytes\n", ft_strlen(av[2]) + 1);
	ft_printf("Client PID: %d\n\n", client_pid);
	ft_memset(&s, 0, sizeof(s));
	if (sigemptyset(&s.sa_mask) < 0)
		ft_printf("Error initializing sa_mask!\n");
	s.sa_sigaction = client_handle;
	s.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	send_kills(ft_atoi(av[1]), av[2]);
	return (0);
}
