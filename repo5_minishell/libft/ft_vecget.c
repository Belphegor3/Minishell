/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:24:28 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:26:02 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vecget(t_vector vec, unsigned int index)
{
	if (index >= vec.length)
		return (NULL);
	return (vec.buffer + (index * vec.item_size));
}
