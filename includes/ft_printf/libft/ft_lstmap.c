/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:58:06 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/24 01:16:46 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_lst;
	void	*new_content;

	new_lst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_content = f(lst-> content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (new_lst);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst-> next;
	}
	return (new_lst);
}
/*
#include <stdio.h>

void	delete(void	*content)
{
	free (content);
}
void	*func(void *content)
{
	content = "J";
	return (content);
}
int	main(void)
{
	t_list	*list = NULL;
	t_list	*l1 = ft_lstnew(ft_strdup(""));
	t_list	*l2 = ft_lstnew(ft_strdup("B"));
	t_list	*l3 = ft_lstnew(ft_strdup("B"));
	t_list	*l4 = ft_lstnew(ft_strdup("B"));
	t_list	*new_list;

	ft_lstadd_back(&list, l1);
	ft_lstadd_back(&l1, l2);
	ft_lstadd_back(&l2, l3);
	ft_lstadd_back(&l3, l4);
	l4->next = NULL;
	new_list = ft_lstmap(list, func, delete);
	while (new_list)
	{
		printf("%s", (char *)new_list->content);
		new_list = new_list->next;
	}
	return (0);
} */
