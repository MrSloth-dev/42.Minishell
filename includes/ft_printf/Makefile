# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 12:54:22 by joao-pol          #+#    #+#              #
#    Updated: 2024/05/03 13:00:40 by joao-pol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

CFLAGS=-Wall -Wextra -Werror -g

PRINTFSRCS = ft_puthex_fd.c ft_putchar_fd.c ft_putnbr_fd.c ft_uputnbr_fd.c ft_putpointer_fd.c ft_putstr_fd.c ft_printf.c

vpath %.c srcs
OBJECTS = $(addprefix srcs/,$(PRINTFSRCS:.c=.o))

LIBDIR = ./libft
LIB = ./libft/libft.a

all : $(NAME)

$(NAME) : $(OBJECTS) $(LIB)
	@cp $(LIB) $(NAME)
	@ar rcs $(NAME) $(OBJECTS)

$(LIB) : $(LIBDIR)
	@make -C $(LIBDIR)

clean :
	make clean -C $(LIBDIR)
	@rm -f $(OBJECTS)

fclean : clean 
	make fclean -C $(LIBDIR)
	@rm -f $(NAME)

re : fclean all

debug: FLAGS += -g
debug: re

.PHONY: all clean fclean re debug
