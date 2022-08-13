/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecaddstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:24:08 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 12:28:50 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int	ft_vecaddstr(t_vector *vec, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_vecadd(vec, &(str[i])))
		{
			perror("");
			return (-1);
		}
		i++;
	}
	return (0);
}
