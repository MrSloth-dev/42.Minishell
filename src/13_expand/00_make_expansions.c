/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:18:38 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/22 15:41:26 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_make_new_cmd(char *str, char *exp, t_iter *h)
{
	char	*r_str;
	int		start_r_str;
	int		len_str;
	char	*tmp;

	len_str = ft_strlen(str + (h->i + h->j));
	h->len = h->i + h->j;
	start_r_str = h->i + h->j;
	r_str = ft_strjoin_free(exp, (ft_substr(str, start_r_str, len_str)));
	tmp = str;
	str = ft_strjoin_free(ft_substr(tmp, 0, h->i - 1), r_str);
	free (tmp);
	return (str);
}

static int	ft_expand_util_edge_cases(t_iter *h, t_shell *sh)
{
	if (h->str[h->i] == '?')
		h->exp = ft_itoa(sh->exit_status);
	else if (h->str[h->i] == '$')
		h->exp = ft_itoa(sh->pid);
	else if (h->str[h->i] == '0')
		h->exp = ft_strdup(sh->prog_name);
	else if (ft_isdigit(h->str[h->i]) == TRUE)
		h->exp = ft_strdup("");
	else
		return (0);
	return (1);
}

static void	ft_expand_util_valid_chars(t_iter *h, t_shell *sh)
{
	h->j = 0;
	while (h->str[h->i + h->j]
		&& (ft_isalnum(h->str[h->i + h->j]) == TRUE
			|| h->str[h->i + h->j] == '_')
		&& ft_is_space(h->str[h->i + h->j]) == FALSE)
	{
		h->j++;
	}
	h->name_var = ft_substr(h->str, h->i, h->j);
	h->exp = ft_expand(h->name_var, sh);
	h->name_var = ft_free(h->name_var);
}

static void	ft_expand_on_this_node(t_iter *h, t_token	*cur, t_shell *sh)
{
	if ((!cur && !cur->content) || !sh || !h)
		return ;
	h->str = cur->content;
	while (h->str[h->i] && h->str[h->i + 1])
	{
		h->j = 1;
		if (h->str[h->i] == '$')
		{
			h->i++;
			if (ft_expand_util_edge_cases(h, sh) == TRUE)
				;
			else if (ft_isalnum(h->str[h->i]) == TRUE || h->str[h->i] == '_')
				ft_expand_util_valid_chars(h, sh);
			else
				h->exp = ft_strjoin_free(ft_strdup("$"),
						ft_substr(h->str, h->i, 1));
			h->k = ft_strlen(h->exp);
			h->str = ft_make_new_cmd(h->str, h->exp, h);
			h->i += h->k - 2;
		}
		h->i++;
	}
	cur->content = h->str;
}

void	ft_make_expansions(t_shell *sh)
{
	t_token	*cur;
	t_iter	h;

	if (!sh || !sh->token_lst || !sh->token_lst->first)
		return ;
	cur = sh->token_lst->first;
	while (cur)
	{
		if (cur->content && cur->type != HERE_DOC)
		{
			if (cur->content && (cur->type == WORD || cur->type > HERE_DOC)
				&& cur->status != IN_SINGLE_QTE)
			{
				h = ft_set_iter(0);
				ft_expand_on_this_node(&h, cur, sh);
				if (ft_strlen(cur->content) == 0)
					cur->maybe_to_delete = TRUE;
			}
		}
		cur = cur->front;
	}
}
