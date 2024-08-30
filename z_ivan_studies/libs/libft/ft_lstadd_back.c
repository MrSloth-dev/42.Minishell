/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:10:41 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/26 18:05:28 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
/*
#include <stdio.h>
int	main(void)
{
	int	size;
	t_list	**test;
	t_list	*lst;
	t_list	*new;
	t_list	*temp;

	lst = ft_lstnew("teste_1");
	new = ft_lstnew("teste_2");

	test = &lst;
	
	ft_lstadd_back(test, new);

	while (lst != NULL)
	{
		temp = lst;
		printf("%s\n", (char *)temp->content);
		lst = lst->next;
		free(temp);
	}
}*/
