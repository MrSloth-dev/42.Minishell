#include "ft_printf.h"
#include "minishell.h"
#include <string.h>


static char	*make_new_cmd(char *str, char *exp, t_iter h)
{
	char	*r_str;
	int		start_r_str;
	int		len_str;
	char	*tmp;

	len_str = ft_strlen(str + (h.i + h.j));
	h.len = h.i + h.j;
	start_r_str = h.i + h.j;
	r_str = ft_strjoin_free(exp, (ft_substr(str, start_r_str, len_str)));
	tmp = str;
	str = ft_strjoin_free(ft_substr(tmp, 0, h.i - 1), r_str);
	free (tmp);
	return (str);
}


void	ft_expand_on_this_node(t_token	*cur, t_shell *sh)
{
	t_iter	h;
	char	*str;
	char	*name_var;
	char	*exp;
	
	if (!cur && !cur->content)
		return ;
	h = set_iter(0);
	exp = NULL;
	name_var = NULL;
	str = cur->content;
	while (str[h.i] && str[h.i + 1])
	{
		h.j = 1;
		if (str[h.i] == '$')
		{
			h.i++;
			if (str [h.i] == '?')
				exp = ft_itoa(sh->exit_status);
			else if (str[h.i] == '$')
				exp = ft_itoa(sh->pid);
			else if (str[h.i] == '0')
				exp = ft_strdup(sh->prog_name);
			else if (ft_isdigit(str[h.i]) == TRUE)
				exp = ft_strdup("");
			else if (ft_isalnum(str[h.i]) == TRUE || str[h.i] == '_')
			{
				h.j = 0;
				while (str[h.i + h.j]
					&& (ft_isalnum(str[h.i + h.j]) == TRUE || str[h.i + h.j] == '_') && ft_is_space(str[h.i + h.j]) == FALSE)
					h.j++;
				name_var = ft_substr(str, h.i, h.j);
				exp = ft_expand(name_var, sh);
				free(name_var);
			}
			else
				exp = ft_strjoin_free(ft_strdup("$"), ft_substr(str, h.i, 1));
			h.k = ft_strlen(exp);
			str = make_new_cmd(str, exp, h);
			h.i += h.k - 2;
		}
		h.i++;
	}
	cur->content = str;
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
