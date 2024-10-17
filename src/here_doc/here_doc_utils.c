#include "minishell.h"

void	ft_make_heredoc_fd(int nb_heredoc, t_shell *sh)
{
	sh->heredoc_fd = ft_calloc(sizeof(int),  nb_heredoc + 1);
	if (!sh->heredoc_fd)
		ft_printf(1, "NEED TO DO SOMETHING HERE LIKE FREE MEM\n"); //check this out!
	sh->heredoc_fd[nb_heredoc] = -1;
}
