CC =cc

CFLAGS=-Wall -Wextra -Werror -g

NAME=libft.a

SOURCES=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	   ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
	   ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
	   ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	   ft_striteri.c ft_strcmp.c\
	   

BSOURCES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		   ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
 
OBJECTS = $(SOURCES:.c=.o)

BOBJECTS = $(BSOURCES:.c=.o)

all : $(NAME)

%.o : %.c
	cc $(CFLAGS) -c $^

$(NAME) : $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

clean :
	@rm -f $(OBJECTS) $(BOBJECTS)

fclean : clean 
	@rm -f $(NAME)

re : fclean all

bonus : $(NAME) $(BOBJECTS)
	@ar rcs $(NAME) $(BOBJECTS)


.PHONY: all clean fclean re bonus
