/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:32:56 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/26 19:14:10 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
static void	print_cont(void *cont)
{
	printf("%s\n", (char *)cont);
}

static void	fun_test(void *lst)
{
	lst = NULL;
}

int	main(void)
{
	int	size;
	t_list	**test;
	t_list	*lst;
	t_list	*new;
	t_list	*temp;

	lst = ft_lstnew("content 1");
	lst->next = ft_lstnew("content 2");
	
	ft_lstiter(lst, print_cont);

	test = &lst;

	ft_lstclear(test, fun_test);
	printf("must be freed!!\n");
}*/
