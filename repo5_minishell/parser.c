/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:09:14 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/12 02:01:44 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "expander.h"

t_syntax_node	*parse_redirection(t_dlist **token, char **envp)
{
	t_syntax_node	*node;

	while (*token && (get_token(*token)->type != GREAT
			&& get_token(*token)->type != LESS
			&& get_token(*token)->type != GREATGREAT)
		&& get_token(*token)->type != PIPE)
		(*token) = (*token)->next;
	if ((*token) == NULL || get_token(*token)->type == PIPE)
		return (NULL);
	node = create_node();
	node->type = REDIRECTION;
	node->token = get_token(*token);
	(*token) = (*token)->next;
	node->left = create_node();
	node->left->type = FILENAME;
	node->left->token = get_token(*token);
	(*token) = (*token)->next;
	if (*token)
		node->right = parse_redirection(token, envp);
	return (node);
}

t_syntax_node	*parse_command(t_dlist **token, char **envp)
{
	t_syntax_node	*node;
	t_dlist			*head_token;

	head_token = *token;
	node = create_node();
	node->type = COMMAND;
	node->right = parse_redirection(token, envp);
	*token = head_token;
	advance_to_next_command_argument(token);
	if ((*token) && get_token(*token)->type == WORD)
		node->left = parse_simple_command(token, envp);
	return (node);
}

t_syntax_node	*parse_job(t_dlist *token, char **envp)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = JOB;
	node->left = parse_command(&token, envp);
	if ((token))
	{
		if (get_token(token)->type == PIPE)
		{
			node->token = get_token(token);
			(token) = (token)->next;
			node->right = parse_job(token, envp);
		}
	}
	return (node);
}

void	remove_empty_tokens(t_dlist **head_token)
{
	t_dlist	*token;
	t_dlist	*next;

	token = *head_token;
	while (token)
	{
		next = token->next;
		if (get_token(token)->type == WORD
			&& ((char *)(get_token(token)->value->buffer))[0] == '\0')
		{
			if ((token)->prev)
				(token)->prev->next = (token)->next;
			else
				*head_token = next;
			if ((token)->next)
				(token)->next->prev = (token)->prev;
			destroy_token(get_token(token));
			ft_dlstdelone(token, NULL);
			token = NULL;
		}
		token = next;
	}
}

t_syntax_node	*parser(t_dlist **head_token, char **envp)
{
	t_syntax_node	*node;
	t_dlist			*token;

	token = *head_token;
	while (token)
	{
		if (get_token(token)->type == WORD)
			expander(&token, get_token(token)->value, envp);
		(token) = (token)->next;
	}
	token = *head_token;
	remove_empty_tokens(head_token);
	if (!(*head_token))
		return (NULL);
	node = parse_job(*head_token, envp);
	return (node);
}
