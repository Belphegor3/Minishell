/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:22:28 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:25:44 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

static void	*forward_copy(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = 0;
	while (n > i)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

static void	*backward_copy(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = n;
	while (i != 0)
	{
		i--;
		((char *)dest)[i] = ((char *)src)[i];
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src > dest)
		forward_copy(dest, src, n);
	else
		backward_copy(dest, src, n);
	return (dest);
}
