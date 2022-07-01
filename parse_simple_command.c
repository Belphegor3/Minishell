/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:26:41 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/23 12:26:42 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	advance_to_next_command_argument(t_tok_list **token)
{
	while (*token && (*token)->token->type != PIPE)
	{
		if ((*token)->token->type == WORD)
			break ;
		if ((*token)->token->type == GREAT
			|| (*token)->token->type == GREATGREAT
			|| (*token)->token->type == LESS)
		{
			(*token) = (*token)->next;
			(*token) = (*token)->next;
		}
	}
}

t_syntax_node	*parse_token_list(t_tok_list **token, char **envp)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = TOKEN_LIST;
	node->left = create_node();
	node->left->type = TOKEN;
	node->left->token = (*token)->token;
	(*token) = (*token)->next;
	advance_to_next_command_argument(token);
	if ((*token) && (*token)->token->type == WORD)
	{
		node->right = parse_token_list(token, envp);
	}
	return (node);
}

t_syntax_node	*parse_simple_command(t_tok_list **token, char **envp)
{
	t_syntax_node	*node;

	if (*token && (*token)->token->type != WORD)
		advance_to_next_command_argument(token);
	node = create_node();
	node->type = SIMPLE_COMMAND;
	node->left = create_node();
	node->left->type = PATHNAME;
	node->left->token = (*token)->token;
	(*token) = (*token)->next;
	advance_to_next_command_argument(token);
	if ((*token) && (*token)->token->type == WORD)
	{
		node->right = parse_token_list(token, envp);
	}
	return (node);
}
