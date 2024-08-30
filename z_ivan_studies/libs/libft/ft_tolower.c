/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:21:00 by isilva-t          #+#    #+#             */
/*   Updated: 2024/04/12 11:23:27 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
#include <stdio.h>
#include <ctype.h>
int     main(void)
{       
        int     c; 
        
        c = 'A';
        printf("antes ft: %d\ndepois MINHA: %d\n", c, ft_tolower(c));       
        printf("antes ft: %d\ndepois ORIGINAL: %d\n", c, tolower(c));
}*/
