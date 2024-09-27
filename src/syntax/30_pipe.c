#include "minishell.h"

static int	ft_is_redir_or_pipe_before(char *str)
{
	while (*str)
	{
		if (*str == '<' || *str == '>' || *str == '|')
			return (TRUE);
		str--;
	}
	return (FALSE);
}

static int	ft_is_pipe_repeated(char *str)
{
	while (*str)
	{
		if (*str == '|')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

static int	ft_this_pipe_have_error(char *str)
{
	if (!*str)
		return (ERR_PIPE);
	if (ft_is_empty_token(str - 2, LEFT_TOKEN) == TRUE)
		return (ERR_PIPE);
	if (ft_is_redir_or_pipe_before(str - 2) == TRUE)
		return (ERR_PIPE);
	while(*str)
	{
		if (ft_is_empty_token(str, RIGHT_TOKEN) == TRUE)
			return (ERR_PIPE);
		if (ft_is_pipe_repeated(str) == TRUE)
			return (ERR_PIPE);
		if (ft_is_space(*str) == FALSE)
			return (FALSE);
		str++;
	}
	return (FALSE);
}

int	ft_check_pipes(char *line)
{
	int	pipe_state;
	int	status;

	pipe_state = FALSE;
	status = NORMAL;
	while (*line)
	{
		status = ft_check_status(status, *line);
		if (*line == '|' && status == NORMAL)
		{
			pipe_state = ft_this_pipe_have_error(++line);
			if (pipe_state != FALSE)
				return (pipe_state);
		}
		line++;
	}
	return (pipe_state);
}
