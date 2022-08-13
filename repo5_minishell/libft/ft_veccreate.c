/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_veccreate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:24:21 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:26:01 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_vector	ft_veccreate(size_t capacity, size_t item_size)
{
	t_vector	result;

	result.buffer = malloc(item_size * capacity);
	if (!result.buffer)
		return (result);
	result.item_size = item_size;
	result.length = 0;
	result.capacity = capacity;
	return (result);
}
