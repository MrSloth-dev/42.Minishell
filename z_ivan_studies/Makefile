# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 16:42:03 by isilva-t          #+#    #+#              #
#    Updated: 2024/08/28 18:01:09 by isilva-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libs/libft/
LIBFT = ./libs/libft/libft.a
GNL = ./libs/gnl/get_next_line.c \
	./libs/gnl/get_next_line_utils.c
GNL_DIR = ./libs/gnl/
##############NOT ALLOWED ON MINISHELL!!!!!!!!!!!
FT_PRINTF = ./libs/ft_printf/ft_printf.c \
	./libs/ft_printf/pf_print_ptr.c \
	./libs/ft_printf/pf_put_nbr_base.c 
FT_PRINTF_DIR = ./libs/ft_printf/
##############NOT ALLOWED ON MINISHELL!!!!!!!
INCLUDES = -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(FT_PRINTF_DIR)
OBJS = ${SRCS:.c=.o}
MSG0 = @echo "Compiling..."
MSG1 = @echo "_________________________________________________________________ Compiled!"

SRCS = $(GNL) $(FT_PRINTF) \
	   ./00.c

NAME = prog

all: $(NAME)

$(NAME):
	$(MSG0);	
	@make -C $(LIBFT_DIR) --silent
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(INCLUDES) -o $(NAME)
	$(MSG1)

clean:
	@make clean -C $(LIBFT_DIR) --silent
	@rm -rf ${OBJS_SERVER} ${OBJS_CLIENT}

fclean: clean
	@make fclean -C $(LIBFT_DIR) --silent
	@rm -rf ${SERVER} ${CLIENT}

re: fclean all
.PHONY: all clean fclean re
