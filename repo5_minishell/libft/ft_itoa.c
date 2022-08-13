/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:18:23 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:25:19 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	get_nb_digits(int n)
{
	int	result;

	result = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		result++;
	}
	return (result);
}

static int	ft_pow(int n, unsigned int p)
{
	if (p == 0)
		return (1);
	if (p == 1)
		return (n);
	return (n * ft_pow(n, p - 1));
}

char	*ft_itoa(int n)
{
	char	*result;
	int		nb_digits;
	int		i;

	i = 0;
	nb_digits = get_nb_digits(n);
	if (n < 0)
		nb_digits++;
	result = malloc(sizeof(char) * (nb_digits + 2));
	if (!result)
		return (0);
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
		i++;
	}
	while (i < nb_digits)
	{
		result[i] = n / ft_pow(10, nb_digits - i - 1) + '0';
		n %= ft_pow(10, nb_digits - i - 1);
		i++;
	}
	result[i] = '\0';
	return (result);
}
