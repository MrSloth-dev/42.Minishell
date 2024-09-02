/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:03:44 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/26 14:41:01 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*ptr_1;
	t_list	*ptr_2;

	ptr_1 = ft_lstnew("NO' UM");
	ptr_2 = ft_lstnew("NO' DOIS");

	printf("ptr_1->content:	%s\n", (char*)ptr_1->content);
	printf("ptr_2->content:	%s\n", (char *)ptr_2->content);

	ft_lstadd_front(&ptr_1, ptr_2);

	printf("\nafter ft:\n");
	printf("ptr_1->content:	%s\n", (char*)ptr_1->content);
	printf("ptr_2->content:	%s\n\n", (char *)ptr_2->content);
	
	printf("ptr_1->next->content:	%s\n", (char *)ptr_1->next->content);
	printf("ptr_2->next->content:	%s\n", (char*)ptr_2->next->content);	

	while (ptr_1 != NULL)
	{
		t_list	*temp = ptr_1;
		ptr_1 = ptr_1->next;
		free(temp);
	}
}*/
