/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:06:54 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/24 00:20:41 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst-> next == NULL)
			return (lst);
		else
			lst = lst-> next;
	}
	return (lst);
}
/*
#include <stdio.h>

int	main()
{
	int	node1 = 10;
	int	node2 = 20;
	t_list *n1 = ft_lstnew(&node1);
	t_list *n2 = ft_lstnew(&node2);
	t_list *last;
	ft_lstadd_front(&n2, n1);
	last = ft_lstlast(n1);
	printf("%d", *(int *)(last-> content));
	return (0);
} */
