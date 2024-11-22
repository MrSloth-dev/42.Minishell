/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:53:59 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/18 11:19:54 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set);
static		int	ft_trim(char c, const char *set);
// static	char	*ft_createstring(const char *str, size_t start, size_t end);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (s1[0] == 0)
		return (ft_strdup(""));
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (ft_trim(s1[i], set))
		i++;
	while (ft_trim(s1[j], set))
		j--;
	if (i == (int)ft_strlen(s1))
		return (ft_strdup(""));
	return (ft_substr(s1, i, j - i + 1));
}

static int	ft_trim(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
