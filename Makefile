################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = minishell
CC = cc
READLINE_FLAG = -lreadline
CFLAGS = -Iincludes -lreadline -g
EFLAGS = -Wall -Wextra -Werror

CLR_RMV = \033[0m
RED	    = \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
CYAN	= \033[1;36m
RM	    = rm -rf

################################################################################
#                                    VALGRIND                                  #
################################################################################
LEAKS_LOG              = ./leaks.log
READLINE_SUPP          = readline.supp
VALGRINDFLAGS          = -s --suppressions=$(READLINE_SUPP) \
                         --tool=memcheck --leak-check=full \
                         --show-leak-kinds=all --track-origins=yes \
                         --track-fds=yes --show-below-main=no \
						 --log-file=$(LEAKS_LOG)


################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

vpath %.h includes
vpath %.c src

HEADER = minishell.h ft_printf.h
PRINTDIR = ./includes/ft_printf/
PRINTFT = ./includes/ft_printf/libftprintf.a

BDIR = src/builtins
EXPDIR = src/expand
SIGNALDIR = src/signals_and_readline
SYNTAXDIR = src/syntax

EXPAND = $(EXPDIR)/expand.c

BUILTIN = $(BDIR)/echo.c \
		$(BDIR)/pwd.c \
		$(BDIR)/cd.c \
		$(BDIR)/env.c \
		$(BDIR)/export.c \
		$(BDIR)/unset.c \
		$(BDIR)/utils.c \
		$(BDIR)/export_utils.c

SIGNAL = $(SIGNALDIR)/readline.c

SYNTAX = $(SYNTAXDIR)/00_syntax_utils.c \
		 $(SYNTAXDIR)/10_quotes.c \
		 $(SYNTAXDIR)/20_redir.c \
		 $(SYNTAXDIR)/30_pipe.c \
		 $(SYNTAXDIR)/40_special_chars.c

SRCS = $(BUILTIN) $(SIGNAL) $(SYNTAX) $(EXPAND)

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
	$(CC) $(MAINI) $(CFLAGS) $(OBJS) $(READLINE_FLAG)  $(PRINTFT) -o minivan
	@echo "$(GREEN)$(NAME) created[0m ✅"

itlk: ivan
	valgrind $(VALGRINDFLAGS) ./minivan

qk: ivan
	./minivan

deb : ivan
	tmux send-keys 'gdbtui ./minivan' C-m Escape

joao : $(OBJS)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)libft$(CLR_RMV)..."
	@make -C $(PRINTDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(OBJS) $(MAINJ) $(CFLAGS) $(PRINTFT) -o minijoao
	@echo "$(GREEN)$(NAME) created[0m ✅"


gdb : joao
	tmux new-window  -n Gdb
	tmux send-keys 'gdbtui ./minijoao' C-m Escape
	tmux split-window -h -l 30
	tmux send-keys -t Gdb.2 'nvim .gdbinit' C-m
	tmux select-pane -t Gdb.1
	@tmux set-hook -t Gdb wigit@github.com:MrSloth-dev/ShellFault.gitndow-linked { run-shell -b "\
		while pgrep -x 'gdb' > /dev/null; do sleep 1; done; \
		tmux wait-for -S gdb_done \
		"}
	tmux wait-for gdb_done
	tmux send-keys -t Gdb.2 ':wqa' C-m Escape
	tmux kill-window -t Gdb


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

