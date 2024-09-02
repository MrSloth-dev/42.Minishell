# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isilva-t <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 09:36:50 by isilva-t          #+#    #+#              #
#    Updated: 2024/04/16 10:43:15 by isilva-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
SOURCES = ft_isalpha.c ft_isdigit.c  ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c \
	ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	ift_atol.c ift_split.c ift_atoi_base.c
BONUS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECTS = ${SOURCES:.c=.o}
BONUS_OBJECTS = ${BONUS:.c=.o}

NAME = libft.a
ARCHIVE = ar -rcs

$(NAME):
	@${CC} -c ${CFLAGS} $(SOURCES) 
	@${ARCHIVE} $(NAME) ${OBJECTS}

bonus: $(NAME)
	@${CC} -c ${CFLAGS} $(BONUS) 
	@${ARCHIVE} $(NAME) ${BONUS_OBJECTS}
	
all: ${NAME}

clean:
	@rm -rf ${OBJECTS} ${BONUS_OBJECTS}

fclean: clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
