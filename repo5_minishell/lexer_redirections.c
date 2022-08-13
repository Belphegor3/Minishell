/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:15:32 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 12:32:51 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "lexer.h"

t_token	*take_greatgreat(char **iter)
{
	t_token		*token;

	token = create_token(GREATGREAT);
	if (!token)
		return (NULL);
	if (ft_vecaddstr(token->value, ">>") == -1)
	{
		destroy_token(token);
		return (NULL);
	}
	(*iter) += 2;
	return (token);
}

t_token	*take_great(char **iter)
{
	t_token		*token;

	token = create_token(GREAT);
	if (!token)
		return (NULL);
	if (ft_vecaddstr(token->value, ">"))
	{
		destroy_token(token);
		return (NULL);
	}
	(*iter)++;
	return (token);
}

t_token	*take_less(char **iter)
{
	t_token		*token;

	token = create_token(LESS);
	if (!token)
		return (NULL);
	if (ft_vecaddstr(token->value, "<"))
	{
		destroy_token(token);
		return (NULL);
	}
	(*iter)++;
	return (token);
}

t_token	*take_redirection(char **iter)
{
	t_token		*token;

	token = NULL;
	if ((*iter)[0] == '>')
	{
		if ((*iter)[1] == '>')
			token = take_greatgreat(iter);
		else
			token = take_great(iter);
	}
	else if ((*iter)[0] == '<')
		token = take_less(iter);
	if (!token)
		return (NULL);
	return (token);
}
