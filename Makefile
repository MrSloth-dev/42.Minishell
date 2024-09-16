################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = minishell
CC = cc
CFLAGS = -Iincludes -g -Wall -Wextra -lreadline

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

HEADER = minishell.h get_next_line.h libft.h

SRCS = src/builtins/echo.c  src/builtins/pwd.c src/builtins/env.c \
	   src/00_signals_and_readline/01_readline.c \

LIBDIR = ./includes/Libft/
LIBFT = ./includes/Libft/libft.a
MAINI = src/main_ivan.c
MAINJ = src/main_joao.c
MAIN = src/main.c

OBJS = $(SRCS:.c=.o)

################################################################################
#                                  Makefile  objs                              #
################################################################################


.PHONY: all clean fclean re debug hell sync_bash

all: $(NAME) $(HEADER) hell

$(NAME): $(OBJS)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)libft$(CLR_RMV)..."
	@make -C $(LIBDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(MAIN) $(OBJS) $(CFLAGS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"

ivan : $(OBJS)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)libft$(CLR_RMV)..."
	@make -C $(LIBDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	$(CC) $(MAINI) $(CFLAGS) $(OBJS)  $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"

joao : $(OBJS)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)libft$(CLR_RMV)..."
	@make -C $(LIBDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(OBJS) $(MAINJ) $(CFLAGS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"

clean:
	@ $(RM) -f $(OBJS)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✅"

fclean: clean
	@ $(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✅"

re : fclean all

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
	@echo "$(RED) A Project developed by Ivan Teixeira && Joao Barbosa$(CLR_RMV)"


.SILENT: all re

