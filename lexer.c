/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:09:04 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:09:06 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static t_token	*take_word(char **iter)
{
	t_token		*token;
	char		special_characters[16];

	ft_strlcpy(special_characters, "|<> \t\n", 16);
	token = create_token(WORD);
	if (!token)
		return (NULL);
	while ((*iter) && (*iter)[0]
			&& ft_strchr(special_characters, (*iter)[0]) == NULL)
	{
		if ((*iter)[0] == '\'')
			take_single_quote(token, iter);
		else if ((*iter)[0] == '\"')
			take_double_quote(token, iter);
		else
		{
			ft_vecadd(token->value, *iter);
			(*iter)++;
		}
	}
	ft_vecadd(token->value, "\0");
	return (token);
}

static t_token	*take_pipe(char **iter)
{
	t_token	*token;

	token = create_token(PIPE);
	if (!token)
		return (NULL);
	ft_vecadd(token->value, *iter);
	ft_vecadd(token->value, "\0");
	(*iter)++;
	return (token);
}

t_tok_list	*lexer(char *line)
{
	t_tok_list	*token_list;
	char		*iter;
	t_token		*token;

	iter = line;
	token_list = NULL;
	while (*iter)
	{
		if (*iter == ' ' || *iter == '\t' || *iter == '\n')
			iter++;
		else
		{
			if (*iter == '|')
				token = take_pipe(&iter);
			else if (*iter == '>' || *iter == '<')
				token = take_redirection(&iter);
			else
				token = take_word(&iter);
			ft_toklstadd_back(&token_list, ft_toklstnew(token));
		}
	}
	return (token_list);
}
