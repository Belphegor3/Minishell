#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main(int argc, char **argv, char **argp)
{
	char	*line;
	t_tok_list		*token_list;
	t_syntax_node	*syntax_tree;
	char	**env;

	env = argp;
	(void)argc;
	(void)argv;
	line = readline("$ ");
	while (line)
	{
		token_list = lexer(line);
		syntax_tree = parser(token_list);
		executor(syntax_tree, argp);
		ft_toklst_clear(&token_list, free);
		delete_syntax_tree(syntax_tree);
		free(line);
		line = readline("$ ");
	}
	return (0);
}
