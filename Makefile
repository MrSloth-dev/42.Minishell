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

VALGRINDONTIME          = -s --suppressions=$(READLINE_SUPP) \
			 --tool=memcheck -q --leak-check=full \
                         --show-leak-kinds=all --track-origins=yes \
                         --track-fds=yes --show-below-main=no




################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

vpath %.h includes
vpath %.c src

HEADER = minishell.h ft_printf.h
PRINTDIR = ./includes/ft_printf/
PRINTFT = ./includes/ft_printf/libftprintf.a

INITDIR = src/00_init
SIGNALDIR = src/01_signals_and_readline
SYNTAXDIR = src/11_syntax
TOKENIZERDIR = src/12_tokenizer
EXPDIR = src/13_expand
H_DOCDIR = src/32_here_doc
PARSEDIR = src/31_parse_data
EXECDIR = ./src/51_execution
BDIR = src/61_builtins
PRINT_MSG_DIR = src/71_print_msg
UTILSDIR = src/81_utils
FREEDIR = src/88_free_stuff

INIT = \
	   $(INITDIR)/00_init.c

SIGNAL = \
		 $(SIGNALDIR)/00_readline.c \
		 $(SIGNALDIR)/01_signal_handle.c

SYNTAX = \
		 $(SYNTAXDIR)/00_syn_utils.c \
		 $(SYNTAXDIR)/10_syn_quotes.c \
		 $(SYNTAXDIR)/20_syn_redir.c \
		 $(SYNTAXDIR)/30_syn_pipe.c \
		 $(SYNTAXDIR)/40_syn_special_chars.c

TOKENIZER = \
			$(TOKENIZERDIR)/00_create_tokens.c \
			$(TOKENIZERDIR)/10_append_node_and_word.c \
			$(TOKENIZERDIR)/11_append_redir.c \
			$(TOKENIZERDIR)/12_join_tokens.c \
			$(TOKENIZERDIR)/13_delete_spaces.c \
			$(TOKENIZERDIR)/14_add_node_exec.c \
			$(TOKENIZERDIR)/88_tokenizer_utils.c

EXPAND = \
		 $(EXPDIR)/00_make_expansions.c \
		 $(EXPDIR)/88_expand.c 

H_DOC = \
		$(H_DOCDIR)/11_do_heredoc_files.c \
		$(H_DOCDIR)/31_here_doc.c \
		$(H_DOCDIR)/88_here_doc_utils.c

PARSE = \
		$(PARSEDIR)/00_make_bin_tree.c

EXEC =	\
		$(EXECDIR)/00_run_cmd.c \
		$(EXECDIR)/01_exec_redir.c \
		$(EXECDIR)/11_exec_builtin.c \
		$(EXECDIR)/21_execve.c

BUILTIN = \
		$(BDIR)/11_echo.c \
		$(BDIR)/21_cd.c \
		$(BDIR)/31_pwd.c \
		$(BDIR)/41_export.c \
		$(BDIR)/42_export_utils.c \
		$(BDIR)/42_export_utils_2.c \
		$(BDIR)/51_unset.c \
		$(BDIR)/61_env.c \
		$(BDIR)/71_exit.c \
		$(BDIR)/81_utils.c 

PRINT = \
		$(PRINT_MSG_DIR)/01_check_file_access.c \
		$(PRINT_MSG_DIR)/02_print_execve_error.c

UTILS = \
		$(UTILSDIR)/11_iter.c \
		$(UTILSDIR)/12_isbuiltin.c \

FREE =	\
		$(FREEDIR)/00_free_shell.c \
		$(FREEDIR)/88_free_and_null.c

WARNING = src/WARNING/print.c

SRCS = $(INIT) $(BUILTIN) $(SIGNAL) $(SYNTAX) $(TOKENIZER) $(PARSE) $(EXPAND) $(FREE) $(WARNING) $(EXEC) $(UTILS) $(H_DOC) $(PRINT)

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
	@make -C $(PRINTDIR) -s
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(CFLAGS) $(EFLAGS) $(MAIN) $(OBJS) $(READLINE_FLAG) $(PRINTFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"
	@mkdir -p $(TMPDIR)

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

va: fclean all
	valgrind $(VALGRINDONTIME) ./$(NAME)

qk: all
	./minishell

deb : re
	tmux send-keys 'gdbtui ./minishell' C-m Escape

norm:
	@norminette | grep -E 'Error:|rror!'

gdb : re
	tmux new-window  -n Gdb
	tmux send-keys 'gdbtui ./minishell' C-m Escape
	tmux split-window -h -l 30
	tmux send-keys -t Gdb.2 'nvim .gdbinit' C-m
	tmux select-pane -t Gdb.1

sync : re
	tmux new-window  -n sync
	tmux send-keys './minishell' C-m Escape
	tmux split-window -h
	tmux send-keys -t sync.2 'bash' C-m
	tmux select-pane -t sync.1
	tmux setw synchronize-panes on

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
	make fclean

te:	$(TESTER_DIR)
	@make re
	@cd $(TESTER_DIR) && ./$(TESTER_BIN) 2>/dev/null | grep /146
	@make fclean

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

