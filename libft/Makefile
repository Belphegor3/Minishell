CC		= cc
FLAGS	= -Wall -Werror -Wextra
SRCS	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c      \
		  ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c  \
		  ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c    \
		  ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
		  ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c \
		  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		  ft_lstmap.c
OBJS	= $(SRCS:.c=.o)

TESTDIR	= tests
TESTS	= ft_atoi_tests.c ft_isdigit_tests.c ft_memset.c ft_strncmp_tests.c \
		ft_bzero_tests.c ft_isprint_tests.c ft_strchr_tests.c \
		ft_strnstr_tests.c ft_calloc_tests.c ft_memchr_tests.c ft_strdup.c \
		ft_strrchr_tests.c ft_isalnum_tests.c ft_memcmp_tests.c \
		ft_strlcat_tests.c ft_tolower.c ft_isalpha_tests.c ft_memcpy_tests.c \
		ft_strlcpy_tests.c ft_toupper.c ft_isascii_tests.c ft_memmove_tests.c \
		ft_strlen_tests.c ft_substr_tests.c ft_strjoin_tests.c \
		ft_strtrim_tests.c ft_split_tests.c ft_itoa_tests.c \
		ft_strmapi_tests.c ft_striteri_tests.c ft_putchar_fd_tests.c \
		ft_putstr_fd_tests.c ft_putendl_fd_tests.c ft_putnbr_fd_tests.c \
		ft_lstnew_tests.c ft_lstadd_front_tests.c ft_lstsize_tests.c \
		ft_lstlast_tests.c ft_lstadd_back_tests.c ft_lstdelone_tests.c \
		ft_lstclear_tests.c ft_lstiter_tests.c ft_lstmap_tests.c
TESTOBJS	= $(patsubst $(TESTDIR)/%.c, $(TESTDIR)/obj/%.o, \
			$(addprefix $(TESTDIR)/, $(TESTS)))

NAME		= libft.a
LIBTESTS	= libtests

all:	$(NAME)

%.o : %.c
	$(CC) -c $(FLAGS) $< -o $@

$(TESTDIR)/obj/%.o: $(TESTDIR)/%.c
	$(CC) -c $(FLAGS) $< -o $@

$(TESTDIR)/obj:
	mkdir $@

$(NAME):	$(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(LIBTESTS):	$(NAME) $(TESTDIR)/obj $(TESTOBJS)
	$(CC) $(FLAGS) $(OBJS) $(TESTOBJS) -o $(LIBTESTS) -L ~/.brew/lib -lcriterion -lbsd -luuid

tests_run:	$(LIBTESTS)
	@./$(LIBTESTS)

clean:
	rm -rf $(OBJS)
	rm -rf *.gcda *.gcno

tclean:
	rm -rf $(TESTDIR)/obj
	rm -f $(LIBTESTS)

fclean:	clean tclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
