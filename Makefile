################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = minishell
CC = cc
READLINE_FLAG = -lreadline
CFLAGS = -Iincludes -g
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
			 --tool=memcheck -q --leak-check=full \
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
EXECDIR = ./src/execution
EXPDIR = src/expand
SIGNALDIR = src/signals_and_readline
SYNTAXDIR = src/syntax
TOKENIZERDIR = src/tokenizer
PARSEDIR = src/parse
FREEDIR = src/free_stuff
INITDIR = src/init
UTILSDIR = src/utils
H_DOCDIR = src/here_doc

INIT = $(INITDIR)/00_init.c

EXPAND = $(EXPDIR)/expand.c \
		 $(EXPDIR)/make_expansions.c

BUILTIN = $(BDIR)/echo.c \
		$(BDIR)/pwd.c \
		$(BDIR)/cd.c \
		$(BDIR)/env.c \
		$(BDIR)/export.c \
		$(BDIR)/unset.c \
		$(BDIR)/utils.c \
		$(BDIR)/export_utils.c \
		$(BDIR)/exit.c

SIGNAL = $(SIGNALDIR)/readline.c

SYNTAX = $(SYNTAXDIR)/00_syntax_utils.c \
		 $(SYNTAXDIR)/10_quotes.c \
		 $(SYNTAXDIR)/20_redir.c \
		 $(SYNTAXDIR)/30_pipe.c \
		 $(SYNTAXDIR)/40_special_chars.c

TOKENIZER = $(TOKENIZERDIR)/00_create_tokens.c \
			$(TOKENIZERDIR)/10_append_node_and_word.c \
			$(TOKENIZERDIR)/11_append_redir.c \
			$(TOKENIZERDIR)/12_join_tokens.c \
			$(TOKENIZERDIR)/13_delete_spaces_and_count_hd.c \
			$(TOKENIZERDIR)/14_add_node_exec.c \
			$(TOKENIZERDIR)/88_tokenizer_utils.c

PARSE = $(PARSEDIR)/00_make_bin_tree.c

EXEC =	$(EXECDIR)/exec_builtin.c \
	$(EXECDIR)/execution.c \
	$(EXECDIR)/pipe.c

UTILS = $(UTILSDIR)/iter.c \
		$(UTILSDIR)/utils.c \

WARNING = src/WARNING/print.c

FREE =	$(FREEDIR)/00_free_shell.c \
	$(FREEDIR)/free.c

H_DOC = $(H_DOCDIR)/here_doc.c \
		$(H_DOCDIR)/here_doc_utils.c

SRCS = $(INIT) $(BUILTIN) $(SIGNAL) $(SYNTAX) $(TOKENIZER) $(PARSE) $(EXPAND) $(FREE) $(WARNING) $(EXEC) $(UTILS) $(H_DOC)

TMPDIR = .tmp

MAIN = src/main.c

OBJS = $(SRCS:.c=.o)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(EFLAGS) -c $< -o $@

################################################################################
#                                  Makefile  rules                             #
################################################################################


.PHONY: all clean fclean re debug hell sync_bash

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)libft$(CLR_RMV)..."
	@mkdir $(TMPDIR)
	@make -C $(PRINTDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(CFLAGS) $(EFLAGS) $(MAIN) $(OBJS) $(READLINE_FLAG) $(PRINTFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"

print : $(OBJS) $(HEADER)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)libft$(CLR_RMV)..."
	@make -C $(PRINTDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(CFLAGS) $(EFLAGS) $(MAIN) $(OBJS) $(READLINE_FLAG) $(PRINTFT)  -D PRINT_DATA=1 -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"
	valgrind $(VALGRINDFLAGS) ./$(NAME)
	cat leaks.log

le: fclean all
	valgrind $(VALGRINDFLAGS) ./$(NAME)
	cat leaks.log

qk: all
	./minishell

deb : re
	tmux send-keys 'gdbtui ./minishell' C-m Escape

norm:
	@norminette | grep rror!

gdb : re
	tmux new-window  -n Gdb
	tmux send-keys 'gdbtui ./minishell' C-m Escape
	tmux split-window -h -l 30
	tmux send-keys -t Gdb.2 'nvim .gdbinit' C-m
	tmux select-pane -t Gdb.1

vgdb : re
	tmux new-window  -n vGdb
	tmux send-keys 'valgrind -q --vgdb-error=0 ./minishell' C-m Escape
	tmux split-window -h
	tmux send-keys -t Gdb.2 'gdbtui ./minishell' C-m
	tmux select-pane -t vGdb.1

clean:
	@ $(RM) -f $(OBJS)
	@ $(RM) $(TMPDIR)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✅"

fclean: clean
	@ $(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✅"

re : fclean all

TESTER_URL = https://github.com/LucasKuhn/minishell_tester.git
TESTER_DIR = minishell_tester
TESTER_BIN = tester

$(TESTER_DIR):
	@git clone $(TESTER_URL) $(TESTER_DIR)

tester: $(TESTER_DIR)
	make re
	@cd $(TESTER_DIR) && ./$(TESTER_BIN)

te:	$(TESTER_DIR)
	@make re
	@cd $(TESTER_DIR) && ./$(TESTER_BIN) 2>/dev/null | grep /146

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


.SILENT: all re gdb

