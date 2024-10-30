/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:45:15 by joao-pol          #+#    #+#             */
/*   Updated: 2024/08/08 11:25:20 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	void	*ft_free(char **str, size_t index);
static	int	ft_count_words(char *str, char c);
static char	*ft_strdupword(char *str, int len);

static char	*ft_get_next_word(char *str, char c, int *i, int *in_quotes)
{
	int	start;
	int	len;

	start = *i;
	len = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' && !(*in_quotes))
		{
			*in_quotes = 1;
			if ((*i)++ | len++)
				continue ;
		}
		if (str[*i] == '\'' && *in_quotes)
		{
			*in_quotes = 0;
			if ((*i)++ | len++)
				continue ;
		}
		if (str[*i] == c && (*in_quotes) == 0)
			break ;
		(*i)++;
		len++;
	}
	return (ft_strdupword(&str[start], len));
}

char	**ft_split(char *str, char c)
{
	char	**split;
	int		iq;
	int		j;
	int		i;

	split = NULL;
	iq = 0;
	i = 0;
	j = 0;
	split = malloc((ft_count_words(str, c) + 1) * sizeof(char *));
	if (!split || !str)
		return (NULL);
	while (str[i] && j < ft_count_words(str, c))
	{
		if ((str[i] == c && !iq) || (str[i] == '\'' && str[i + 1] == '\''))
			i++;
		else
		{
			split[j] = ft_get_next_word(str, c, &i, &iq);
			if (!split)
				return (ft_free(split, j), NULL);
			j++;
		}
	}
	return (split[j] = NULL, split);
}

static int	ft_count_words(char *str, char c)
{
	int	in_quotes;
	int	count;
	int	i;

	if (!str)
		return (0);
	in_quotes = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && !in_quotes && (i == 0 || str[i - 1] == c))
			count++;
		if (str[i] == '\'')
			in_quotes = !in_quotes;
		i++;
	}
	return (count);
}

static char	*ft_strdupword(char *str, int len)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len && str[i])
	{
		if (str[i] == '\'')
			i++;
		dup[j++] = str[i++];
	}
	dup[j] = '\0';
	return (dup);
}

static void	*ft_free(char **str, size_t index)
{
	size_t	j;

	j = 0;
	while (j < index)
	{
		free(str[j]);
		j++;
	}
	free(str);
	return (NULL);
}
