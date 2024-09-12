#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int	pipefd[2];
	pid_t	pid1, pid2;

	if (ac == 2)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		
		if ((pid1 = fork()) == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid1 == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);

			char	*ls_args[] = {"/bin/ls", NULL};
			printf("doing execve ls\n");
			execve("/bin/ls", ls_args, NULL);
			
			perror("execve");
			exit(EXIT_FAILURE);
		}

		if ((pid2 = fork()) == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);

			char *grep_args[] = {"/bin/grep", av[1], NULL};
			printf("doing execve grep\n");
			execve("/bin/grep", grep_args, NULL);

			perror("execve");
			exit(EXIT_FAILURE);
		}



		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
		wait(NULL);
	}
	else
		printf("need argument!\n");
	return (0);


}
