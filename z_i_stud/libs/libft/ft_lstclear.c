/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:55:22 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/29 12:12:15 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		del(temp->content);
		free (temp);
	}
	*lst = NULL;
}
/*
static void	fun_test(void *lst)
{
	lst = NULL;
}

#include <stdio.h>
int	main(void)
{
	int	size;
	t_list	**test;
	t_list	*lst;
	t_list	*new;
	t_list	*temp;

	lst = ft_lstnew("teste_1");
	lst->next = ft_lstnew("teste_2");

	test = &lst;
	
	ft_lstclear(test, fun_test);
	printf("must be freed!!\n");
}*/
