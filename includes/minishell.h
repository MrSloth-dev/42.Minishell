/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:56:06 by joao-pol          #+#    #+#             */
/*   Updated: 2024/08/29 15:56:46 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H_
# define MINISHELL_H_

# include <unistd.h>
# include "get_next_line.h"
# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

// 00_signals_and_readline
void	ft_readline();

#endif //MINISHELL_H_

