/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:26:41 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/05 10:24:23 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_syntax_node	*parse_token_list(t_dlist **token, char **envp)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = TOKEN_LIST;
	node->left = create_node();
	node->left->type = TOKEN;
	node->left->token = get_token((*token));
	(*token) = (*token)->next;
	advance_to_next_command_argument(token);
	if ((*token) && get_token((*token))->type == WORD)
	{
		node->right = parse_token_list(token, envp);
	}
	return (node);
}

t_syntax_node	*parse_simple_command(t_dlist **token, char **envp)
{
	t_syntax_node	*node;

	advance_to_next_command_argument(token);
	if (*token == NULL || get_token(*token)->type != WORD)
		return (NULL);
	node = create_node();
	node->type = SIMPLE_COMMAND;
	node->left = create_node();
	node->left->type = PATHNAME;
	node->left->token = get_token(*token);
	(*token) = (*token)->next;
	advance_to_next_command_argument(token);
	if ((*token) && get_token(*token)->type == WORD)
	{
		node->right = parse_token_list(token, envp);
	}
	return (node);
}
