/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_to_next_command_argument.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:59:42 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/12 02:00:28 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"

void	advance_to_next_command_argument(t_dlist **token)
{
	while (*token && get_token(*token)->type != PIPE)
	{
		if (get_token(*token)->type == WORD)
			break ;
		if (get_token(*token)->type == GREAT
			|| get_token(*token)->type == GREATGREAT
			|| get_token(*token)->type == LESS)
		{
			(*token) = (*token)->next;
			(*token) = (*token)->next;
		}
	}
}
