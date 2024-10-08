#include "minishell.h"

void	ft_expand_on_this_node(t_token	*cur, t_shell *sh)
{
	int	i;
	int	j;
	int	len;
	char	*str;
	char	*to_join;
	char	*tmp;
	
	i = 0;
	j = 0;
	if (!cur && !cur->content)
		return ;
	str = ft_strdup(cur->content);
	len = ft_strlen(str);
	while (str[i])
	{
		j = 1;
		if (str[i] == '$')
		{
			if (str[i + 1])
			{
				while (str[i + 1 + j] &&
		   			(str[i + 1 + j] != '$' && ft_is_space(str[i + 1 + j]) != TRUE))
					j++;
				ft_printf(1, "%d\n", j);

				to_join = ft_expand(ft_substr(str, i + 1, j), sh);
				ft_printf(1, "%s\n", to_join);

				tmp = ft_strjoin_free(ft_substr(str, 0, i), to_join);
				ft_printf(1, "%s\n\n", tmp);

				i += 1 + j;
			}
		}
		i++;
	}


	tmp = cur->content;
	cur->content = str;
	free(tmp);
}


void	ft_make_expansions(t_shell *sh)
{
	t_token	*cur;

	if (!sh || !sh->token_lst || !sh->token_lst->first)
		return ;
	cur = sh->token_lst->first;
	while (cur)
	{
		if (cur->content && cur->type == WORD)
		{
			ft_printf(1, "lets make expansion \n\n");
			ft_expand_on_this_node(cur, sh);
		}
		cur = cur->next;
	}
}
