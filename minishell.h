#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <assert.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
typedef struct	s_as_tree_node
{
	int	type;
	char	*sz_data;
	struct	s_as_tree_node *left;
	struct	s_as_tree_node *righ;
}	t_as_tree_node;

int	execute_simple_command(t_syntax_node *command_tree,
		t_redirections *redirect, char *envp[]);
#endif
