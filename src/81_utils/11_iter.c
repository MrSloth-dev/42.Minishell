/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:16:05 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/22 11:44:36 by isilva-t         ###   ########.fr       */
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
	h.fd = n;
	h.len = n;
	h.pid = n;
	h.std_in = n;
	h.std_out = n;
	h.status = n;
	h.delimiter = NULL;
	h.file = NULL;
	h.prog_name = NULL;
	h.exp = NULL;
	h.name_var = NULL;
	h.str = NULL;
	h.line = NULL;
	h.tmp = NULL;
	h.cur = NULL;
	h.cur_left = NULL;
	h.cur_right = NULL;
	return (h);
}
