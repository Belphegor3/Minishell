/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:07:01 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/15 03:07:45 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"

void	destroy_token(t_token *token)
{
	if (token)
	{
		ft_vecdestroy((token->value));
		free(token->value);
		free(token);
	}
}
