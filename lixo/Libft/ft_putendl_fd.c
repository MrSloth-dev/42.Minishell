/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:35:03 by joao-pol          #+#    #+#             */
/*   Updated: 2024/04/15 16:36:55 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	char	nl;

	nl = '\n';
	ft_putstr_fd(str, fd);
	write(fd, &nl, 1);
}
/*
#include <unistd.h>
int	main()
{
	ft_putendl_fd("Hello World!", 1);
	return (0);
}*/
