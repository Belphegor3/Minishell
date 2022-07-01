#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include "../minishell.h"
#include "../parser.h"
#include "../lexer.h"

extern char **environ;

static void	serialize_tree(t_syntax_node *tree, char buffer[], int *buffer_index)
{
	if (tree)
	{
		buffer[*buffer_index] = tree->type + '0';
		(*buffer_index)++;
		buffer[*buffer_index] = ' ';
		(*buffer_index)++;
		if (tree->token)
		{
			ft_memcpy(buffer + *buffer_index, ft_vecget(*(tree->token->value), 0), tree->token->value->length);
			(*buffer_index) += tree->token->value->length - 1;
			buffer[*buffer_index] = ' ';
			(*buffer_index)++;
		}
		serialize_tree(tree->left, buffer, buffer_index);
		serialize_tree(tree->right, buffer, buffer_index);
	}
	else
	{
		buffer[*buffer_index] = 'N';
		(*buffer_index)++;
		buffer[*buffer_index] = ' ';
		(*buffer_index)++;
	}
}

static void cr_assert_tree(char *line, char *expected_serialized_tree)
{
	t_syntax_node	*node;
	t_tok_list		*tokens;
	char	buffer[256];
	int		buffer_index;

	buffer_index = 0;
	tokens = lexer(line);
	node = parser(tokens, environ);
	serialize_tree(node, buffer, &buffer_index);
	buffer[buffer_index - 1] = '\0';
	cr_assert_str_eq(buffer, expected_serialized_tree);
	delete_syntax_tree(node);
	ft_toklst_clear(&tokens, NULL);
}

Test(tree, create_node)
{
	t_syntax_node	*node;

	node = create_node();
	cr_assert(node != NULL);
	cr_assert(node->left == NULL);
	cr_assert(node->right == NULL);
	node->left = create_node();
	cr_assert(node->left != NULL);
	cr_assert(node->left->left == NULL);
	cr_assert(node->left->right == NULL);
	delete_syntax_tree(node);
}

Test(parser, empty_token_list)
{
	cr_assert_tree("\0", "N");
}

Test(parser, one_word)
{
	cr_assert_tree("ls", "0 1 2 4 ls N N N N N");
}

Test(parser, multiple_words)
{
	cr_assert_tree("ls -la", "0 1 2 4 ls N N 5 6 -la N N N N N");
}

Test(parser, multiple_words2)
{
	cr_assert_tree("ls -la ~", "0 1 2 4 ls N N 5 6 -la N N 5 6 ~ N N N N N");
}

Test(parser, one_pipe)
{
	cr_assert_tree("ls -l | grep c", "0 | 1 2 4 ls N N 5 6 -l N N N N 0 1 2 4 grep N N 5 6 c N N N N N");
}

Test(parser, one_pipe2)
{
	cr_assert_tree("ls | grep c", "0 | 1 2 4 ls N N N N 0 1 2 4 grep N N 5 6 c N N N N N");
}

Test(parser, one_pipe3)
{
	cr_assert_tree("ls | cat", "0 | 1 2 4 ls N N N N 0 1 2 4 cat N N N N N");
}

Test(parser, multiple_pipes)
{
	cr_assert_tree("ls -l | grep c | cat -e", "0 | 1 2 4 ls N N 5 6 -l N N N N 0 | 1 2 4 grep N N 5 6 c N N N N 0 1 2 4 cat N N 5 6 -e N N N N N");
}

Test(parser, redirection_great)
{
	cr_assert_tree("cat Makefile > out.txt", "0 1 2 4 cat N N 5 6 Makefile N N N 3 > 7 out.txt N N N N");
}

Test(parser, redirection_great2)
{
	cr_assert_tree("cat > out.txt Makefile", "0 1 2 4 cat N N 5 6 Makefile N N N 3 > 7 out.txt N N N N");
}

Test(parser, redirection_less)
{
	cr_assert_tree("grep a < Makefile", "0 1 2 4 grep N N 5 6 a N N N 3 < 7 Makefile N N N N");
}

Test(parser, redirection_greatgreat)
{
	cr_assert_tree("cat Makefile >> out.txt", "0 1 2 4 cat N N 5 6 Makefile N N N 3 >> 7 out.txt N N N N");
}

Test(parser, single_quote1)
{
	cr_assert_tree("ls '-la'", "0 1 2 4 ls N N 5 6 -la N N N N N");
}

Test(parser, single_quote2)
{
	cr_assert_tree("l's'''", "0 1 2 4 ls N N N N N");
}

Test(parser, double_quotes1)
{
	cr_assert_tree("ls \"> out.txt\"", "0 1 2 4 ls N N 5 6 > out.txt N N N N N");
}
