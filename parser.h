#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

enum node_type
{
	JOB,
	COMMAND,
	SIMPLE_COMMAND,
	REDIRECTION,
	PATHNAME,
	TOKEN_LIST,
	TOKEN,
	FILENAME
};

typedef struct	s_syntax_node
{
	enum node_type			type;
	t_token					*token;
	struct s_syntax_node	*left;
	struct s_syntax_node	*right;
}t_syntax_node;

t_syntax_node	*create_node(void);
void			delete_syntax_tree(t_syntax_node *root);
t_syntax_node	*parser(t_tok_list *token);
#endif
