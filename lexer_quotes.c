/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:18:40 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/15 03:18:40 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"

void	take_single_quote(t_token *token, char **iter)
{
	ft_vecadd(token->value, *iter);
	(*iter)++;
	while ((*iter)[0] && (*iter)[0] != '\'')
	{
		ft_vecadd(token->value, *iter);
		(*iter)++;
	}
	if ((*iter)[0])
	{
		ft_vecadd(token->value, *iter);
		(*iter)++;
	}
}

void	take_double_quote(t_token *token, char **iter)
{
	ft_vecadd(token->value, *iter);
	(*iter)++;
	while ((*iter)[0] && (*iter)[0] != '\"')
	{
		ft_vecadd(token->value, *iter);
		(*iter)++;
	}
	if ((*iter)[0])
	{
		ft_vecadd(token->value, *iter);
		(*iter)++;
	}
}
