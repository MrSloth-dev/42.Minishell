#include "ft_printf.h"
#include "minishell.h"

int	ft_how_much_consecutive_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_is_space(str[i]) == TRUE)
		i++;
	printf("consecutive %d spaces\n", i);
	return (i);
}

void	ft_shellfault(t_shell *sh)
{
	ft_tokenizer(sh->token_lst, sh->line);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = ft_init_shell(envp);
	while (1)
	{
		ft_readline(sh);
		if (ft_have_syntax_error(sh) != FALSE)
			ft_print_syntax_error(ft_have_syntax_error(sh));
		else
			ft_shellfault(sh);
	}
	return (0);
}
