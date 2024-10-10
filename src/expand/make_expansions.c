#include "ft_printf.h"
#include "minishell.h"
#include <string.h>


static char	*make_new_cmd(char *str, char *exp, t_iter h)
{
	char	*r_str;
	int		start_r_str;
	int		len_str;

	len_str = ft_strlen(str + (h.i + h.j));
	h.len = h.i + h.j;
	start_r_str = h.i + h.j;
	r_str = ft_strjoin_free(exp, (ft_substr(str, start_r_str, len_str)));
	ft_printf(1, "str: %s      right: %s\n", str, r_str);
	str = ft_strjoin_free(ft_substr(str, 0, h.i - 1), r_str);
	return (str);
}



					// name_var = ft_substr(str, h.i + 1, h.j);
					// exp = ft_expand(name_var, sh);
					// free(name_var);


void	ft_expand_on_this_node(t_token	*cur, t_shell *sh)
{
	t_iter	h;
	char	*str;
	char	*name_var;
	char	*exp;
	
	if (!cur && !cur->content)
		return ;
	h = set_h(0);
	exp = NULL;
	name_var = NULL;
	str = ft_strdup(cur->content);
	while (str[h.i])
	{
		ft_printf(1, "vou olhar para o caractere \"%c\"  na posicao %d\n", str[h.i], h.i);
		h.j = 1;
		if (str[h.i] == '$')
		{
			if (str[h.i + 1])
			{
				h.i++;
				if (str [h.i] == '?')
					exp = ft_itoa(sh->exit_status);
				else if (str[h.i] == '$')
					exp = ft_itoa(sh->pid);
				else if (str[h.i] == '0')
					exp = ft_strdup("minishell");
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
					ft_printf(1, "Joao, era suposto ser este o resultado? %s\n", exp);
					free(name_var);
				}
				h.k = ft_strlen(exp);
				ft_printf(1, "antes de mexer na str: %s\n", str);
				str = make_new_cmd(str, exp, h);
				ft_printf(1, "olha como ficou a str: %s\n", str);
				h.i += h.k - 2;
			}
			else
			{
				ft_printf(1, "ass_hole\n");
				h.i++;
				str = make_new_cmd(str, ft_strdup("$"), h);
			}
		}
		h.i++;
	}

	exp = cur->content;
	cur->content = str;
	free (exp);
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
