/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecdestroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:24:24 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:26:02 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_vecdestroy(t_vector *vec)
{
	free(vec->buffer);
	vec->item_size = 0;
	vec->length = 0;
	vec->capacity = 0;
	vec->buffer = NULL;
}
