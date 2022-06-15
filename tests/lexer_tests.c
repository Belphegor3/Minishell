#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "lexer.h"

static void	cr_assert_lexer(char *line, enum e_token_type expected_types[], char *expected_slices[])
{
	t_tok_list	*token_list;
	t_tok_list	*elem;
	t_slice	slice;
	int		i;

	token_list = lexer(line);
	elem = token_list;
	i = 0;
	while (elem)
	{
		cr_assert(elem->token->type == expected_types[i]);
		slice = elem->token->slice;
		cr_assert(strncmp(expected_slices[i], slice.start, slice.length) == 0 && slice.length == strlen(expected_slices[i]));
		elem = elem->next;
		i++;
	}
	ft_toklst_clear(&token_list, &free);
}

Test(lexer, empty_line)
{
	char				*line = "\0";
	enum e_token_type	expected_types[] = {};
	char				*expected_slices[] = {};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, one_word)
{
	char				*line = "ls";
	enum e_token_type	expected_types[] = {WORD};
	char				*expected_slices[] = {"ls"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, multiple_words)
{
	char				*line = "ls -la";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_slices[] = {"ls", "-la"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, multiple_words2)
{
	char				*line = "ls -la ~";
	enum e_token_type	expected_types[] = {WORD, WORD, WORD};
	char				*expected_slices[] = {"ls", "-la", "~"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, single_quotes)
{
	char				*line = "echo 'Hello world!'";
	enum e_token_type	expected_types[] = {WORD, QUOTE};
	char				*expected_slices[] = {"echo", "Hello world!"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, double_quotes)
{
	char				*line = "echo \"Hello world!\"";
	enum e_token_type	expected_types[] = {WORD, DQUOTE};
	char				*expected_slices[] = {"echo", "Hello world!"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, pipe)
{
	char				*line = "ls -l | grep c";
	enum e_token_type	expected_types[] = {WORD, WORD, PIPE, WORD, WORD};
	char				*expected_slices[] = {"ls", "-l", "|", "grep", "c"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, pipe2)
{
	char				*line = "ls | grep c";
	enum e_token_type	expected_types[] = {WORD, PIPE, WORD, WORD};
	char				*expected_slices[] = {"ls", "|", "grep", "c"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, multiple_pipes)
{
	char				*line = "ls -l | grep c | cat -e";
	enum e_token_type	expected_types[] = {WORD, WORD, PIPE, WORD, WORD, PIPE, WORD, WORD};
	char				*expected_slices[] = {"ls", "-l", "|", "grep", "c", "|", "cat", "-e"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, redirection_great)
{
	char				*line = "cat Makefile > out.txt";
	enum e_token_type	expected_types[] = {WORD, WORD, GREAT, WORD};
	char				*expected_slices[] = {"cat", "Makefile", ">", "out.txt"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, redirection_less)
{
	char				*line = "grep a < Makefile";
	enum e_token_type	expected_types[] = {WORD, WORD, LESS, WORD};
	char				*expected_slices[] = {"grep", "a", "<", "Makefile"};

	cr_assert_lexer(line, expected_types, expected_slices);
}

Test(lexer, redirection_greatgreat)
{
	char				*line = "cat Makefile >> out.txt";
	enum e_token_type	expected_types[] = {WORD, WORD, GREATGREAT, WORD};
	char				*expected_slices[] = {"cat", "Makefile", ">>", "out.txt"};

	cr_assert_lexer(line, expected_types, expected_slices);
}
