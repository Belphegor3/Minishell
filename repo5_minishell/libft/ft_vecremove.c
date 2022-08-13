/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 05:43:45 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/17 05:43:46 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <assert.h>

void	ft_vecremove(t_vector *vec, unsigned int first, unsigned int last)
{
	if (last >= first && first < vec->length)
	{
		if (last > vec->length)
			last = vec->length;
		if (vec->length > 1)
		{
			ft_memmove(vec->buffer + (first * vec->item_size),
				vec->buffer + ((last + 1) * vec->item_size),
				vec->item_size * (vec->length - last - 1));
			vec->length -= last - first + 1;
		}
		else if (vec->length > 0)
			vec->length--;
	}
}
