/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:57:17 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/12 06:13:54 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_token	*create_token(enum e_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		perror ("minishell");
		return (NULL);
	}
	new_token->type = type;
	new_token->value = malloc(sizeof(t_vector));
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	*(new_token->value) = ft_veccreate(1, sizeof(char));
	return (new_token);
}
