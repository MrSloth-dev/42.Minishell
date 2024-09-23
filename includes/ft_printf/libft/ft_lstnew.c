/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:50:01 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/19 13:50:21 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/* #include <stdio.h>
int	main()
{
	t_list	*l1;
	t_list	*l2;

	int i = 42;
	char	*str = "Helloooo";
	l1 = ft_lstnew(&i);
	l2 = ft_lstnew(&str);
	printf("%d", *((int *)l1->content));
	printf("%s", *((char **)l2->content));
}
*/
