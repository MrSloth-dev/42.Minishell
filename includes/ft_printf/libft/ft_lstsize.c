/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:55:41 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/24 00:06:38 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst-> next;
		count++;
	}
	return (count);
}
/*
#include <stdio.h>
int main()
{
	int n1 = 10;
	int n2 = 20;
	int n3 = 30;
	t_list	*node1 = ft_lstnew(&n1);
	t_list	*node2 = ft_lstnew(&n2);
	t_list	*node3 = ft_lstnew(&n3);
	ft_lstadd_front(&node3, node2);
	ft_lstadd_front(&node2, node1);
	printf("%d", ft_lstsize(node1));
} */
