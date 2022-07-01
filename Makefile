CC		= cc
FLAGS	= -Wall -Werror -Wextra -g3 #-fsanitize=address -fsanitize=leak -fsanitize=undefined

SRCS	= lexer.c parser.c executor.c execute_simple_command.c \
			get_file_path.c close_standard_fds.c ft_tok_lst.c create_token.c \
			destroy_token.c lexer_redirections.c lexer_quotes.c \
			expand_variables.c expand_quotes.c syntax_tree_utils.c \
			parse_simple_command.c builtins/cd.c builtins/echo.c	\
			builtins/env.c builtins/exit.c builtins/export.c		\
			builtins/pwd.c builtins/unset.c builtins/utils.c		\
			builtins/utils_cd.c	builtins/utils_export.c				\
			builtins/utils_unset.c builtins/execute_builtins.c

OBJS	= $(SRCS:.c=.o)

TESTDIR	= tests
TESTS	= lexer_tests.c parser_tests.c executor_tests.c \
		  expand_variables_tests.c #get_file_path_tests.c

TESTOBJS	= $(patsubst $(TESTDIR)/%.c, $(TESTDIR)/obj/%.o, \
			$(addprefix $(TESTDIR)/, $(TESTS)))

NAME		= minishell

LIBFT		= libft/libft.a

all:	$(NAME)

%.o : %.c
	$(CC) -c $(FLAGS) -I libft -I. $< -o $@

$(LIBFT):
	$(MAKE) -C libft

$(TESTDIR)/obj/%.o: $(TESTDIR)/%.c
	$(CC) -c $(FLAGS) -I libft -I. $< -o $@

$(TESTDIR)/obj:
	mkdir $@

$(NAME):	$(LIBFT) $(OBJS) main.o
	$(CC) $(FLAGS) main.c $(OBJS) -o $(NAME) -lncurses -lreadline -I libft -I. libft/libft.a

unit_tests:	$(LIBFT) $(TESTDIR)/obj $(OBJS) $(TESTOBJS)
	$(CC) $(FLAGS) $(OBJS) $(TESTOBJS) -o unit_tests -L ~/.brew/lib -lcriterion -lbsd -luuid -lncurses -lreadline -I libft -I. libft/libft.a

tests_run:	unit_tests
	$(MAKE) tests_run -C libft
	@./unit_tests

tclean:
	rm -rf $(TESTDIR)/obj
	rm -f unit_tests

clean: tclean
	$(MAKE) fclean -C libft
	rm -rf $(OBJS)
	rm -rf main.o

fclean:	clean tclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean tclean fclean re tests_run
