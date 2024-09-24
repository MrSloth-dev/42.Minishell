#include "minishell.h"

int	ft_have_unclosed_qtes(char *line)
{
	int	have_uncl_qte;
	char	find_this;

	have_uncl_qte = FALSE;
	while (*line)
	{
		if (*line == P_SINGLE_QTE || *line == P_DOUBLE_QTE)
		{
			find_this = *line++;
			while (*line && *line != find_this)
				line++;
			if (!*line || *line != find_this)
				have_uncl_qte = ERR_UNCLOSED_QTE;
		}
		if (*line)
		line++;
	}
	return (have_uncl_qte);
}
