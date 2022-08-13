/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:27:59 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/09 14:19:20 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*result;

	result = malloc(sizeof(t_dlist));
	if (!result)
		return (NULL);
	result->content = content;
	result->prev = NULL;
	result->next = NULL;
	return (result);
}
