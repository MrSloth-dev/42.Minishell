/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_create_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:02:53 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/21 17:20:55 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

		//ft_append_node(token_lst, ft_strdup("\x02"), WORD, status);
static int	ft_append_inside_quotes(t_token_lst *token_lst,
								char *str, int status)
{
	int		len;
	char	qte;

	qte = *str;
	len = 1;
	while (str[len] && str[len] != qte)
		len++;
	if (len == 1)
		ft_append_node(token_lst, ft_strdup("\x02"), WORD, status);
	else
		ft_append_node(token_lst, ft_substr(str + 1, 0, len - 1), WORD, status);
	return (len + 1);
}

static void	ft_create_tokens_accessory(t_token_lst *token_lst, char *line,
								int *i, int status)
{
	if (!token_lst || !line)
		return ;
	if (ft_is_space(line[*i]) == TRUE)
	{
		*i += ft_how_much_consecutives_spaces(line + *i);
		ft_append_node(token_lst, ft_strdup(" "), WHITE_SPACE, status);
	}
	else if (line[*i] == '|')
		*i += ft_append_node(token_lst, ft_strdup("|"), ND_PIPE, status);
	else if (line[*i] == '<' || line[*i] == '>')
		*i += ft_append_redir(token_lst, line + *i, status);
}

void	ft_create_tokens(t_token_lst *token_lst, char *line)
{
	int	status;
	int	i;

	i = 0;
	status = NORMAL;
	ft_append_node(token_lst, ft_strdup("ND_EXEC "), ND_EXEC, NORMAL);
	while (line[i])
	{
		if (ft_is_word(line[i]) == TRUE)
		{
			i += ft_append_word(token_lst, line + i, WORD, status);
			if (!line[i])
				break ;
		}
		status = ft_check_status(status, line[i]);
		if (status != NORMAL)
		{
			i += ft_append_inside_quotes(token_lst, line + i, status);
			status = NORMAL;
		}
		else
			ft_create_tokens_accessory(token_lst, line, &i, status);
	}
}
