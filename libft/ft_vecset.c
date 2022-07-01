/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:24:31 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:26:03 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vecset(t_vector vec, unsigned int index, void *item)
{
	if (index >= vec.length)
		return (-1);
	ft_memcpy((void *)(vec.buffer + index * vec.item_size),
		item,
		vec.item_size);
	return (0);
}
