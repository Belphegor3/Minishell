/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:23:55 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:25:56 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	size_t			len_little;

	len_little = ft_strlen(little);
	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (i + j < len && big[i + j] && little[j]
			&& big[i + j] == little[j] && j < len_little)
			j++;
		if (j == len_little)
			return (((char *)&big[i]));
		i++;
	}
	return (0);
}
