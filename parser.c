#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"

t_syntax_node	*create_node(void)
{
	t_syntax_node	*node;

	node = malloc(sizeof(t_syntax_node));
	node->token = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void			delete_syntax_tree(t_syntax_node *root)
{
	if (root)
	{
		if (root->left)
			delete_syntax_tree(root->left);
		if (root->right)
			delete_syntax_tree(root->right);
		free(root);
	}
}

t_syntax_node	*parse_token_list(t_tok_list **token)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = TOKEN_LIST;
	node->left = create_node();
	node->left->type = TOKEN;
	node->left->token = (*token)->token;
	if ((*token)->next && (*token)->next->token->type == WORD)
	{
		*token = (*token)->next;
		node->right = parse_token_list(token);
	}
	return (node);
}

t_syntax_node	*parse_simple_command(t_tok_list **token)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = SIMPLE_COMMAND;
	node->left = create_node();
	node->left->type = PATHNAME;
	node->left->token = (*token)->token;
	if ((*token)->next && (*token)->next->token->type == WORD)
	{
		(*token) = (*token)->next;
		node->right = parse_token_list(token);
	}
	(*token) = (*token)->next;
	return (node);
}

t_syntax_node	*parse_redirection(t_tok_list **token)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = REDIRECTION;
	node->token = (*token)->token;
	(*token) = (*token)->next;
	node->left = create_node();
	node->left->type = FILENAME;
	node->left->token = (*token)->token;
	(*token) = (*token)->next;
	if (*token && ((*token)->token->type == GREAT || (*token)->token->type == LESS || (*token)->token->type == GREATGREAT))
		node->right = parse_redirection(token);
	return (node);
}

t_syntax_node	*parse_command(t_tok_list **token)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = COMMAND;
	node->left = parse_simple_command(token);
	if (*token)
	{
		if ((*token)->token->type == GREAT || (*token)->token->type == LESS || (*token)->token->type == GREATGREAT)
		{
			node->right = parse_redirection(token);
		}
	}
	return (node);
}

t_syntax_node	*parse_job(t_tok_list **token)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = JOB;
	node->left = parse_command(token);
	if ((*token))
	{
		if ((*token)->token->type == PIPE)
		{
			(*token) = (*token)->next;
			node->right = parse_job(token);
		}
	}
	return (node);
}

t_syntax_node	*parser(t_tok_list *token)
{
	t_syntax_node	*node;

	if (!token)
		return (NULL);
	node = parse_job(&token);
	return (node);
}
