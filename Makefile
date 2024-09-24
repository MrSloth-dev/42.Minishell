################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = minishell
CC = cc
CFLAGS = -Iincludes -lreadline -g -Q
EFLAGS = -Wall -Wextra -Werror

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

HEADER = minishell.h get_next_line.h ft_printf.h
PRINTDIR = ./includes/ft_printf/
PRINTFT = ./includes/ft_printf/libftprintf.a

BUILTINDIR = src/builtins
SIGNALDIR = src/signals_and_readline
SYNTAXDIR = src/syntax

BUILTIN = $(BUILTINDIR)/echo.c  $(BUILTINDIR)/pwd.c $(BUILTINDIR)/env.c $(BUILTINDIR)/export.c $(BUILTINDIR)/unset.c\

SIGNAL = $(SIGNALDIR)/readline.c
SYNTAX = $(SYNTAXDIR)/10_quotes.c

SRCS = $(BUILTIN) $(SIGNAL) $(SYNTAX)

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
	@make -C $(PRINTDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(MAIN) $(OBJS) $(CFLAGS) $(PRINTFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"

error : CFLAGS += $(EFLAGS)
ivan : $(OBJS)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)libft$(CLR_RMV)..."
	@make -C $(PRINTDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	$(CC) $(MAINI) $(CFLAGS) $(OBJS)  $(PRINTFT) -o minivan
	@echo "$(GREEN)$(NAME) created[0m ✅"

joao : $(OBJS)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)libft$(CLR_RMV)..."
	@make -C $(PRINTDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(OBJS) $(MAINJ) $(CFLAGS) $(PRINTFT) -o minijoao
	@echo "$(GREEN)$(NAME) created[0m ✅"

gdb : joao
	# @if [tmux has-session -t "$1" 2>/dev/null]; then\
	tmux new-window  -n Gdb
	tmux send-keys 'gdbtui ./minijoao' C-m Escape
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

