/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:15:32 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/15 03:15:33 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

t_token	*take_greatgreat(char **iter)
{
	t_token		*token;

	token = create_token(GREATGREAT);
	if (!token)
		return (NULL);
	ft_vecadd(token->value, *iter);
	ft_vecadd(token->value, *iter);
	ft_vecadd(token->value, "\0");
	(*iter) += 2;
	return (token);
}

t_token	*take_great(char **iter)
{
	t_token		*token;

	token = create_token(GREAT);
	if (!token)
		return (NULL);
	ft_vecadd(token->value, *iter);
	ft_vecadd(token->value, "\0");
	(*iter)++;
	return (token);
}

t_token	*take_less(char **iter)
{
	t_token		*token;

	token = create_token(LESS);
	if (!token)
		return (NULL);
	ft_vecadd(token->value, *iter);
	ft_vecadd(token->value, "\0");
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
