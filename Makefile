CC		= cc
FLAGS	= -Wall -Werror -Wextra

SRCS	= lexer.c parser.c executor.c execute_simple_command.c \
			get_file_path.c
OBJS	= $(SRCS:.c=.o)

TESTDIR	= tests
TESTS	= lexer_tests.c parser_tests.c executor_tests.c get_file_path_tests.c

TESTOBJS	= $(patsubst $(TESTDIR)/%.c, $(TESTDIR)/obj/%.o, \
			$(addprefix $(TESTDIR)/, $(TESTS)))

NAME		= minishell

all:	$(NAME)

%.o : %.c
	$(CC) -c $(FLAGS) -I libft -I. $< -o $@

$(TESTDIR)/obj/%.o: $(TESTDIR)/%.c
	$(CC) -c $(FLAGS) -I libft -I. $< -o $@

$(TESTDIR)/obj:
	mkdir $@

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) main.c $(OBJS) -o $(NAME) -lreadline -lncurses -I libft -I. libft/libft.a

unit_tests:	$(TESTDIR)/obj $(OBJS) $(TESTOBJS)
	$(CC) $(FLAGS) $(OBJS) $(TESTOBJS) -o unit_tests -L ~/.brew/lib -lbsd -luuid -lreadline -lncurses -lcriterion -I libft -I. libft/libft.a

tests_run:	unit_tests
	@./unit_tests

clean:
	rm -rf $(OBJS)
	rm -rf main.o

tclean:
	rm -rf $(TESTDIR)/obj
	rm -f unit_tests

fclean:	clean tclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
