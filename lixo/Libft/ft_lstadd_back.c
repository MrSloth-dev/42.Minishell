/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:21:06 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/24 01:20:39 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst)
	{
		last = ft_lstlast(*lst);
		last -> next = new;
	}
	else
		*lst = new;
}
/* #include <stdio.h>

int	main(void)
{
	t_list	*l1 = ft_lstnew("l1");
	t_list	*l2 = ft_lstnew("l2");
	t_list	*l3 = ft_lstnew("l3");
	t_list	*l4 = ft_lstnew("l4");

	ft_lstadd_back(&l1, l2);
	ft_lstadd_back(&l2, l3);
	ft_lstadd_back(&l3, l4);

	while (l1)
	{
		printf("%s\n", (char *)l1->content);
		l1 = l1->next;
	}
	return (0);
} */
