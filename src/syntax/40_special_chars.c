#include "minishell.h"

int	ft_check_special_char(char *line)
{
	char	*special_chars;
	int		status;

	special_chars = "\\;()&!*";
	status = NORMAL;
	while (*line)
	{
		status = ft_check_status(status, *line);
		if (ft_strchr(special_chars, *line) && status == NORMAL)
			return ((int)*line);
		line++;
	}
	return (FALSE);
}
