/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:16:05 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/09 13:16:09 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_iter	ft_set_iter(int n)
{
	t_iter	h;

	h.c = n;
	h.i = n;
	h.j = n;
	h.k = n;
	h.len = n;
	h.str = NULL;
	h.line = NULL;
	h.tmp = NULL;
	h.cur = NULL;
	h.cur_left = NULL;
	h.cur_right = NULL;
	return (h);
}


