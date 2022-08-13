/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_unexpected_token.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:03:11 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 12:21:26 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_unexpected_pipe(t_dlist *token_list)
{
	if (get_token(token_list)->type == PIPE)
		return (-1);
	token_list = token_list->next;
	while (token_list)
	{
		if (get_token(token_list)->type == PIPE)
			if (!token_list->next || get_token(token_list->next)->type == PIPE)
				return (-1);
		token_list = token_list->next;
	}
	return (0);
}

static void	print_syntax_error(char *token_str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_str, 2);
	ft_putstr_fd("'\n", 2);
}

int	check_for_unexpected_token(t_dlist *token_list)
{
	if (check_for_unexpected_pipe(token_list) != 0)
	{
		print_syntax_error("|");
		return (-1);
	}
	while (token_list && token_list->next)
	{
		if (get_token(token_list)->type != WORD
			&& get_token(token_list)->type != PIPE)
		{
			if (get_token(token_list->next)->type != WORD)
				return (print_syntax_error((char *)
						get_token(token_list->next)->value->buffer), -1);
		}
		token_list = token_list->next;
	}
	if (get_token(token_list)->type != WORD
		&& get_token(token_list)->type != PIPE)
	{
		print_syntax_error("newline");
		return (-1);
	}
	return (0);
}
