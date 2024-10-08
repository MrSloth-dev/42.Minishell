#include "minishell.h"

void	ft_expand_on_this_node(t_token	*cur, t_shell *sh)
{
	int	i;
	int	j;
	int	k;
	char	*str;
	char	*name_var;
	char	*exp;
	char	*new_cmd;
	
	new_cmd = NULL;
	i = 0;
	j = 1;
	k = 0;
	if (!cur && !cur->content)
		return ;
	str = cur->content;
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
				//ft_printf(1, "%d\n", j);
				name_var = ft_substr(str, i + 1, j);
				exp = ft_expand(name_var, sh);
				free(name_var);
				//ft_printf(1, "%s\n", exp);

				if (!new_cmd)
					new_cmd = ft_strjoin_free(ft_substr(str, k, i), exp);
				else
					new_cmd = ft_strjoin_free(new_cmd, exp);

				//ft_printf(1, "%s\n\n", new_cmd);

				i += j;
				k = i;
			}
		}
		i++;
	}
	if (new_cmd != NULL)
	{
		cur->content = new_cmd;
		free (str);
	}
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
			//need to se into de ft, if dont have a dollar, I HAVE A BUG!
			ft_expand_on_this_node(cur, sh);
		}
		cur = cur->next;
	}
}
