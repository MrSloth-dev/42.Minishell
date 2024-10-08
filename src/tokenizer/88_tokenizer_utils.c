#include "minishell.h"


// || c == '$'
int	ft_is_word(char c)
{
	if (!c)
		return (FALSE);
	if (c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '"'
		|| c == '\''
		|| ft_is_space(c) == TRUE)
		return (FALSE);
	else
		return (TRUE);
}

int	ft_how_much_consecutives_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_space(str[i]) == TRUE)
		i++;
	return (i);
}


