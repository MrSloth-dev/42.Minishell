#include "ft_printf.h"
#include "minishell.h"
#include <string.h>

t_iterator	set_h(int n)
{
	t_iterator	h;

	h.i = n;
	h.j = n;
	h.k = n;
	return (h);
}

// char	*make_new_cmd(char *new_cmd)
// {
// 					if (!new_cmd)
// 						new_cmd = ft_strjoin_free(ft_substr(str, k, i), exp);
// 					else
// 						new_cmd = ft_strjoin_free(new_cmd, exp);
// }



void	ft_expand_on_this_node(t_token	*cur, t_shell *sh)
{
	t_iterator	h;
	char	*str;
	char	*name_var;
	char	*exp;
	char	*new_cmd;
	
	h = set_h(0);
	new_cmd = NULL;
	if (!cur && !cur->content)
		return ;
	str = cur->content;
	while (str[h.i])
	{
		h.j = 1;
		if (str[h.i] == '$')
		{
			if (str[h.i + 1])
			{
				if (str[h.i + 1] != '$' && ft_isdigit(str[h.i + 1]) == FALSE)
				{
					while (str[h.i + 1 + h.j]
						&& 		(
						str[h.i + 1 + h.j] != '$'
						&& (ft_isalnum(str[h.i + 1 + h.j]) == TRUE || str[h.i + 1 + h.j] == '_')
						&& ft_is_space(str[h.i + 1 + h.j]) != TRUE
								)
						)
						h.j++;
					name_var = ft_substr(str, h.i + 1, h.j);
					exp = ft_expand(name_var, sh);
					free(name_var);
					if (!new_cmd)
						new_cmd = ft_strjoin_free(ft_substr(str, h.k, h.i), exp);
					else
						new_cmd = ft_strjoin_free(new_cmd, exp);
				}
				else if (str[h.i + 1] == '$')
				{

				}


				h.i += h.j;
				h.k = h.i;
			}
			else
			{
				if (!new_cmd)
					new_cmd = ft_strjoin_free(ft_substr(str, h.k, h.i), ft_strdup("$"));
				else
					new_cmd = ft_strjoin_free(new_cmd, ft_strdup("$"));
			}
			//ft_printf(1, "%s\n\n", new_cmd);
		}
		h.i++;
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
		if (cur->content && cur->type != HERE_DOC)
		{
			if (cur->content && cur->type == WORD && cur->status != IN_SINGLE_QTE)
				ft_expand_on_this_node(cur, sh);
		}
		cur = cur->next;
	}
}
