#include "minishell.h"

void ft_free_lst_shell(t_shell *sh)
{
	t_token	*cur;
	t_token	*tmp;
	
	if (sh->token_lst && sh->token_lst->first)
	{
		cur = sh->token_lst->first;
		while (cur)
		{
			tmp = cur;
			cur = cur->front;
			tmp->content = ft_free(tmp->content);
			tmp = ft_free(tmp);
		}
	}
	sh->token_lst = ft_free(sh->token_lst);
}

void	*ft_free_envp(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
	envp = NULL;
	return (NULL);
}

void	ft_clean_here_doc(t_shell *sh)
{
	int		i;
	char 	*name;

	name = NULL;
	i = 0;
	while (i++ != sh->nb_heredoc)
	{
		name = ft_itoa(sh->nb_heredoc);
		unlink(name);
		name = ft_free(name);
	}
	if (sh->nb_heredoc > 0)
		sh->heredoc_fd = ft_free(sh->heredoc_fd);
}

