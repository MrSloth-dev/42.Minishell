/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:31:42 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/24 00:40:50 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}
/*
#include <stdio.h>
void	delete(void *content)
{
	free (content);
}
int	main(void)
{
	t_list	*node1 = ft_lstnew(ft_strdup("node1"));
	t_list	*node2 = ft_lstnew(ft_strdup("node2"));
	t_list	*node3 = ft_lstnew(ft_strdup("node3"));

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;

	printf("node1: %s\n", (char *)node1->content);
	printf("node2: %s\n", (char *)node2->content);
	printf("node3: %s\n", (char *)node3->content);

	ft_lstclear(&node1, delete);

	printf("node1: %s\n", (char *)node1->content);
	printf("node2: %s\n", (char *)node2->content);
	printf("node3: %s\n", (char *)node3->content);
	return (0);
} */
