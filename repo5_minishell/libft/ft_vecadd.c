/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:24:17 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:26:00 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_vecresize(t_vector *vec)
{
	void	*new_buff;

	new_buff = malloc(sizeof(vec->item_size) * vec->capacity * 2);
	if (!new_buff)
		return (-1);
	vec->capacity *= 2;
	ft_memcpy(new_buff, vec->buffer, vec->length * vec->item_size);
	free(vec->buffer);
	vec->buffer = new_buff;
	return (0);
}

int	ft_vecadd(t_vector *vec, void *item)
{
	if (vec->length >= vec->capacity)
	{
		if (ft_vecresize(vec) == -1)
			return (-1);
	}
	ft_memcpy((void *)(vec->buffer + vec->length * vec->item_size),
		item,
		vec->item_size);
	vec->length++;
	return (0);
}
