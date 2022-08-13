CFLAGS		?= -Wall -Werror -Wextra -MMD -MP -g
LDFLAGS 	?=

SRCS		= main.c lexer.c parser.c executor.c execute_simple_command.c \
				destroy_token.c lexer_redirections.c lexer_quotes.c \
				expand_variables.c expand_quotes.c syntax_tree_utils.c \
				parse_simple_command.c builtins/cd.c builtins/echo.c \
				builtins/env.c builtins/exit.c builtins/export.c \
				builtins/pwd.c builtins/unset.c builtins/utils.c \
				builtins/utils_cd.c	builtins/utils_export.c \
				builtins/utils_unset.c builtins/execute_builtins.c \
				check_for_unexpected_token.c close_standard_fds.c \
				create_token.c get_token.c get_file_path.c	\
				signal.c advance_to_next_command_argument.c \
				execute_redirection.c


LIBFT		:= libft/libft.a
NAME		:= minishell
BUILD_DIR	:= .build
DEPS		:= $(SRCS:%.c=$(BUILD_DIR)/%.d)
OBJS		:= $(DEPS:.d=.o)

all:	$(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lncurses -lreadline -I libft -I. libft/libft.a

clean:
	$(MAKE) fclean -C libft
	rm -rf $(BUILD_DIR)

fclean:	clean
	rm -f $(NAME)

re: fclean all

malloc_test: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic $(OBJS) -o $@ -lncurses -lreadline -I libft -I. libft/libft.a -L. -lmallocator

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: all clean fclean re
