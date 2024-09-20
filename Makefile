################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = minishell
CC = cc
CFLAGS = -Iincludes -Wall -Wextra -lreadline -g -Q

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

SRCS = src/builtins/echo.c  src/builtins/pwd.c src/builtins/env.c src/builtins/export.c \
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
	$(CC) $(MAINI) $(CFLAGS) $(OBJS)  $(LIBFT) -o minivan
	@echo "$(GREEN)$(NAME) created[0m ✅"

joao : $(OBJS)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)libft$(CLR_RMV)..."
	@make -C $(LIBDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(OBJS) $(MAINJ) $(CFLAGS) $(LIBFT) -o minijoao
	@echo "$(GREEN)$(NAME) created[0m ✅"

gdb : joao
	# @if [tmux has-session -t "$1" 2>/dev/null]; then\
	tmux new-window  -n Gdb
	tmux send-keys 'gdbtui ./minishell' C-m Escape
	tmux split-window -h -l 30
	tmux send-keys -t Gdb.2 'nvim .gdbinit' C-m
	tmux select-pane -t Gdb.1
	@tmux set-hook -t Gdb window-linked { run-shell -b "\
		while pgrep -x 'gdb' > /dev/null; do sleep 1; done; \
		tmux wait-for -S gdb_done \
		"}
	tmux wait-for gdb_done
	tmux send-keys -t Gdb.2 ':wqa' C-m Escape
	tmux kill-window -t Gdb
	# fi


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

