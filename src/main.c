#include "libft.h"
#include "minishell.h"
#include <unistd.h>

char	*get_next_line(int fd);

int	main(void)
{
	char	*line;
	int		fd;

	fd = 0;
	write(2, "\033[2J\033[H", 8);
	write(STDOUT_FILENO, "Please write your command >>  ", 30);
	line = get_next_line(fd);
	while (line)
	{
		write(STDOUT_FILENO, "Please write your command >>  ", 30);
		line = get_next_line(fd);
		if (ft_strlen(line) == 0 || ft_strncmp("exit", line, 5))
		{
			free(line);
			return (0);
		}
	}
	return (0);
}
