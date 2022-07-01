/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:39:35 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/22 23:39:36 by jfoucher         ###   ########.fr       */
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

int	ft_vecinsert(t_vector *vec, unsigned int index, void *items,
							unsigned int nb_items)
{
	if (index > vec->length)
		index = vec->length;
	while (vec->length + nb_items > vec->capacity)
	{
		if (ft_vecresize(vec) == -1)
			return (-1);
	}
	ft_memmove(vec->buffer + ((index + nb_items) * vec->item_size),
		vec->buffer + ((index) * vec->item_size),
		(vec->length - index) * vec->item_size);
	ft_memmove(vec->buffer + ((index) * vec->item_size),
		items, (nb_items) * vec->item_size);
	vec->length += nb_items;
	return (0);
}
