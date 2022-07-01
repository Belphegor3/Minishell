/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:09:14 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:09:19 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "expander.h"

t_syntax_node	*parse_redirection(t_tok_list **token, char **envp)
{
	t_syntax_node	*node;

	while (*token && ((*token)->token->type != GREAT
			&& (*token)->token->type != LESS
			&& (*token)->token->type != GREATGREAT)
		&& (*token)->token->type != PIPE)
		(*token) = (*token)->next;
	if ((*token) == NULL || (*token)->token->type == PIPE)
		return (NULL);
	node = create_node();
	node->type = REDIRECTION;
	node->token = (*token)->token;
	(*token) = (*token)->next;
	node->left = create_node();
	node->left->type = FILENAME;
	node->left->token = (*token)->token;
	(*token) = (*token)->next;
	if (*token)
		node->right = parse_redirection(token, envp);
	return (node);
}

t_syntax_node	*parse_command(t_tok_list **token, char **envp)
{
	t_syntax_node	*node;
	t_tok_list		*head_token;

	node = create_node();
	node->type = COMMAND;
	head_token = *token;
	while ((*token) && (*token)->token->type != PIPE)
	{
		if ((*token)->token->type == WORD)
			expander(token, (*token)->token->value, envp);
		(*token) = (*token)->next;
	}
	*token = head_token;
	node->right = parse_redirection(token, envp);
	*token = head_token;
	node->left = parse_simple_command(token, envp);
	return (node);
}

t_syntax_node	*parse_job(t_tok_list **token, char **envp)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = JOB;
	node->left = parse_command(token, envp);
	if ((*token))
	{
		if ((*token)->token->type == PIPE)
		{
			node->token = (*token)->token;
			(*token) = (*token)->next;
			node->right = parse_job(token, envp);
		}
	}
	return (node);
}

t_syntax_node	*parser(t_tok_list *token, char **envp)
{
	t_syntax_node	*node;

	if (!token)
		return (NULL);
	node = parse_job(&token, envp);
	return (node);
}
