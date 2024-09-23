/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:28:48 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/24 00:12:56 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*list = NULL;
	t_list	*l1 = ft_lstnew("node 1");
	t_list	*l2 = ft_lstnew("node 2");

	ft_lstadd_front(&list, l1);
	ft_lstadd_front(&list, l2);

	t_list	*newlist = list;
	while (newlist)
	{
		printf("%s\n", (char *)newlist->content);
		newlist = newlist->next;
	}
	return (0);
} */
