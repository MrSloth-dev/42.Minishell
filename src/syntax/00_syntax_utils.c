#include "minishell.h"

void	ft_print_syntax_error(int error)
{
	char	*name;

	name = "ShellFault: syntax error near";
	if (error == ERR_REDIR_LEFT)
		ft_printf(STDERR_FILENO, "%s unexpected token `<'\n", name);
	else if (error == ERR_REDIR_RIGHT)
		ft_printf(STDERR_FILENO, "%s unexpected token `>'\n", name);
	else if (error == ERR_DBLE_REDIR_LEFT)
		ft_printf(STDERR_FILENO, "%s unexpected token `<<'\n", name);
	else if (error == ERR_DBLE_REDIR_RIGHT)
		ft_printf(STDERR_FILENO, "%s unexpected token `>>'\n", name);
	else if (error == ERR_PIPE_AFTER_REDIR)
		ft_printf(STDERR_FILENO, "%s unexpected token `|'\n", name);
	else if (error == ERR_UNCLOSED_QTE)
		ft_printf(STDERR_FILENO, "%s unclosed quotes\n", name);
	else if (error == ERR_EMPTY_TOKEN)
		ft_printf(STDERR_FILENO, "%s unexpected token `newline'\n", name);
	else if (error == ERR_PIPE)
		ft_printf(STDERR_FILENO, "%s unexpected token `|'\n", name);
	else
		ft_printf(STDERR_FILENO, "%s unexpected token `%c'\n", name, (char)error);
}

int	ft_check_status(int status, char c)
{
	if (c == P_DOUBLE_QTE && status == NORMAL)
		status = IN_DOUBLE_QTE;
	else if (c == P_SINGLE_QTE && status == NORMAL)
		status = IN_SINGLE_QTE;
	else if (c == P_DOUBLE_QTE && status == IN_DOUBLE_QTE)
		status = NORMAL;
	else if (c == P_SINGLE_QTE && status == IN_SINGLE_QTE)
		status = NORMAL;
	return (status);
}

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13)
		|| c == ' ')
		return (TRUE);
	else
		return (FALSE);
}

int	ft_is_empty_token(char *line, int direction)
{
	while (*line)
	{
		if (ft_is_space(*line) == TRUE)
		{
			if (direction == RIGHT_TOKEN)
				line++;
			else
				line--;
		}
		else
			return (FALSE);
	}
	return (TRUE);
}
