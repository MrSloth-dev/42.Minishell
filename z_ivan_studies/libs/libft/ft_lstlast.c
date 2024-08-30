/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:41:52 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/26 18:16:23 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;
	int		size;

	last = (t_list *)lst;
	size = ft_lstsize(lst);
	while (size > 1)
	{
		last = last->next;
		size--;
	}
	return (last);
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*lst; 
	t_list	*last;

	lst = ft_lstnew("teste_1");
	lst->next = ft_lstnew("teste_2");
	lst->next->next = ft_lstnew("teste_3");

	last = ft_lstlast(lst);
	printf("Last: %s\n", (char *)last->content);
	while (lst != NULL)
	{
		t_list	*temp = lst;
		lst = lst->next;
		free(temp);
	}
}*/
