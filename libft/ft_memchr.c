/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:22:09 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:25:42 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (((unsigned char *)s)[i] != c && i < n)
		i++;
	if (((unsigned char *)s)[i] == c)
		return (&((unsigned char *)s)[i]);
	return (0);
}
