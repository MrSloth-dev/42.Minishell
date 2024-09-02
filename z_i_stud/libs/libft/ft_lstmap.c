/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:45:32 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/29 16:12:33 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	auto t_list * ret_list, *current;
	if (!lst || !f || !del)
		return (NULL);
	current = ft_lstnew(f(lst->content));
	if (!current)
	{
		ft_lstclear(&current, del);
		return (NULL);
	}
	ret_list = current;
	lst = lst->next;
	while (lst)
	{
		current->next = ft_lstnew(f(lst->content));
		if (!current->next)
		{
			ft_lstclear(&ret_list, del);
			return (NULL);
		}
		lst = lst->next;
		current = current->next;
	}
	current->next = NULL;
	return (ret_list);
}
/*
#include <stdio.h>
static void	*print_fun(void *cont)
{
	printf("print_fun %s\n", (char *)cont);
	return (cont);
}

static void	del(void *lst)
{
	lst = NULL;
	printf("del ok!\n");
}

int	main(void)
{
	t_list	*lst;
	t_list	*to_free;
	t_list *temp;

	lst = ft_lstnew("content 1");
	lst->next = ft_lstnew("content 2");
	printf ("lst created;\n");

	to_free = ft_lstmap(lst, print_fun, del);
	printf ("ft_lstmap returned;\n");

	ft_lstclear(&to_free, del);
	printf("to_free freed!\n");
	ft_lstclear(&lst, del);
	printf("lst freed. END!!\n");
	return (0);
}*/
