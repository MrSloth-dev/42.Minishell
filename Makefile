################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = minishell
CC = cc
CFLAGS = -Iincludes -g -Wall -Werror -Wextra 

CLR_RMV = \033[0m
RED	    = \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
CYAN	= \033[1;36m
RM	    = rm -rf


################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

vpath %.h includes
vpath %.c src
HEADER = minishell.h

SRCS = main.c \

OBJS = $(addprefix src/, $(SRCS:.c=.o))

################################################################################
#                                  Makefile  objs                              #
################################################################################


all: $(NAME) $(HEADER) hell

$(NAME): $(OBJS) $(LIB)
	@echo "$(MINISHELL)"
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)ft_printf$(CLR_RMV)..."
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"

clean:
	@ $(RM) -f $(OBJS)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✅"

fclean: clean
	@ $(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✅"

re : fclean all

debug: CFLAGS += -g
debug: re

hell :
	@echo "$(RED) <-. (\`-')    _      <-. (\`-')_   _       (\`-').->  (\`-')  _       "
	@echo "    \\(OO )_  (_)        \\( OO) ) (_)      (OO )__   ( OO).-/    <-.       <-.    "
	@echo " ,--./  ,-.) ,-(\`-') ,--./ ,--/  ,-(\`-') ,--. ,'-' (,------.  ,--. )    ,--. )   "
	@echo " |   \`.'   | | ( OO) |   \\ |  |  | ( OO) |  | |  |  |  .---'  |  (\`-')  |  (\`-') "
	@echo " |  |'.'|  | |  |  ) |  . '|  |) |  |  ) |  \`-'  | (|  '--.   |  |OO )  |  |OO ) "
	@echo " |  |   |  |(|  |_/  |  |\\    | (|  |_/  |  .-.  |  |  .--'  (|  '__ | (|  '__ | "
	@echo " |  |   |  | |  |'-> |  | \\   |  |  |'-> |  | |  |  |  \`---.  |     |'  |     |' "
	@echo " \`--'   \`--' \`--'    \`--'  \`--'  \`--'    \`--' \`--'  \`------'  \`-----'   \`-----'  "
	@echo "                                                                                 $(CLR_RMV)"


.PHONY: all clean fclean re debug hell
.SILENT:
