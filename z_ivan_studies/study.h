/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:25 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/28 18:00:01 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "./libs/libft/libft.h"
# include "./libs/ft_printf/ft_printf.h"

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# define STR_SIZE 128  
# define TRUE 1
# define FALSE 0

# define EMOJI_1 "\xF0\x9F\x94\xA5"
# define EMOJI_2 "\xF0\x9F\x98\x80"
# define EMOJI_3 "\xF0\x9F\x8E\x89"

typedef struct s_data
{
	char			data[STR_SIZE];
	struct s_data	*prev;
	struct s_data	*begin;
	struct s_data	*next;
}				t_data;

void	append_node(t_data **lst, int *i);

#endif
