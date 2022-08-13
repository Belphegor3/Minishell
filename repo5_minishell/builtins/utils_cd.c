/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:54:28 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 14:54:29 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	found_name_with_value(char **exp, char *to_find)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (exp[i])
	{
		j = 0;
		k = 0;
		if (exp[i][j] == to_find[k])
		{
			while (to_find[k] && exp[i][j] && exp[i][j] == to_find[k])
			{
				j++;
				k++;
			}
			if ((exp[i][j] && (exp[i][j] == '=' && !to_find[k])) ||
				(!exp[i][j] && !to_find[k]))
				return (i);
		}
		i++;
	}
	return (-1);
}
