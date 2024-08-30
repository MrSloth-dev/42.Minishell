/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:46:31 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/26 14:40:48 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*counter;

	size = 0;
	counter = (t_list *)lst;
	while (counter)
	{
		size++;
		counter = counter->next;
	}
	return (size);
}
/*
#include <stdio.h>
int	main(void)
{
	int	size;
	t_list	*lst; 

	lst = ft_lstnew("teste_1");
	lst->next = ft_lstnew("teste_2");
	lst->next->next = ft_lstnew("teste_3");

	size = ft_lstsize(lst);
	printf("Size: %d\n", size);
	while (lst != NULL)
	{
		t_list	*temp = lst;
		printf("%s\n", (char *)temp->content);
		lst = lst->next;
		free(temp);
	}
}*/
