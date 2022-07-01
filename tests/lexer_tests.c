#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "lexer.h"

static void	cr_assert_lexer(char *line, enum e_token_type expected_types[], char **expected_values)
{
	t_tok_list	*token_list;
	t_tok_list	*elem;
	int		i;

	token_list = lexer(line);
	elem = token_list;
	i = 0;
	while (elem)
	{
		cr_assert(elem->token->type == expected_types[i]);
		cr_assert_str_eq(ft_vecget(*(elem->token->value), 0), expected_values[i]);
		elem = elem->next;
		i++;
	}
	ft_toklst_clear(&token_list, ((void *)(void *)(*destroy_token)));
}

Test(lexer, empty_line)
{
	char				*line = "\0";
	enum e_token_type	expected_types[] = {};
	char				*expected_values[] = {};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, one_word)
{
	char				*line = "ls";
	enum e_token_type	expected_types[] = {WORD};
	char				*expected_values[] = {"ls"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, multiple_words)
{
	char				*line = "ls -la";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"ls", "-la"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, multiple_words2)
{
	char				*line = "ls -la ~";
	enum e_token_type	expected_types[] = {WORD, WORD, WORD};
	char				*expected_values[] = {"ls", "-la", "~"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, single_quotes)
{
	char				*line = "printf 'Hello world!\n'";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"printf", "'Hello world!\n'"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, single_quotes2)
{
	char				*line = "ls -'la'";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"ls", "-'la'"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, single_quotes3)
{
	char				*line = "ls ''-la";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"ls", "''-la"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, single_quotes4)
{
	char				*line = "''ls -la";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"''ls", "-la"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, single_quotes5)
{
	char				*line = "l's'''";
	enum e_token_type	expected_types[] = {WORD};
	char				*expected_values[] = {"l's'''"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, double_quotes)
{
	char				*line = "printf \"Hello world!\n\"";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"printf", "\"Hello world!\n\""};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, double_quotes2)
{
	char				*line = "ls -\"la\"";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"ls", "-\"la\""};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, double_quotes3)
{
	char				*line = "ls \"\"-la";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"ls", "\"\"-la"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, double_quotes4)
{
	char				*line = "\"\"ls -la";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"\"\"ls", "-la"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, double_quotes5)
{
	char				*line = "ls \"> out.txt\"";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"ls", "\"> out.txt\""};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, pipe)
{
	char				*line = "ls -l | grep c";
	enum e_token_type	expected_types[] = {WORD, WORD, PIPE, WORD, WORD};
	char				*expected_values[] = {"ls", "-l", "|", "grep", "c"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, pipe2)
{
	char				*line = "ls | grep c";
	enum e_token_type	expected_types[] = {WORD, PIPE, WORD, WORD};
	char				*expected_values[] = {"ls", "|", "grep", "c"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, multiple_pipes)
{
	char				*line = "ls -l | grep c | cat -e";
	enum e_token_type	expected_types[] = {WORD, WORD, PIPE, WORD, WORD, PIPE, WORD, WORD};
	char				*expected_values[] = {"ls", "-l", "|", "grep", "c", "|", "cat", "-e"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, redirection_great)
{
	char				*line = "cat Makefile > out.txt";
	enum e_token_type	expected_types[] = {WORD, WORD, GREAT, WORD};
	char				*expected_values[] = {"cat", "Makefile", ">", "out.txt"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, redirection_less)
{
	char				*line = "grep a < Makefile";
	enum e_token_type	expected_types[] = {WORD, WORD, LESS, WORD};
	char				*expected_values[] = {"grep", "a", "<", "Makefile"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, redirection_greatgreat)
{
	char				*line = "cat Makefile >> out.txt";
	enum e_token_type	expected_types[] = {WORD, WORD, GREATGREAT, WORD};
	char				*expected_values[] = {"cat", "Makefile", ">>", "out.txt"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, simple_variable_expansion)
{
	char				*line = "ls $HOME";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"ls", "$HOME"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, simple_variable_expansion2)
{
	char				*line = "printf $PATH";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"printf", "$PATH"};

	cr_assert_lexer(line, expected_types, expected_values);
}

Test(lexer, dquote_dollar)
{
	char				*line = "printf \"$PATH\"";
	enum e_token_type	expected_types[] = {WORD, WORD};
	char				*expected_values[] = {"printf", "\"$PATH\""};

	cr_assert_lexer(line, expected_types, expected_values);
}
