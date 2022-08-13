/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:23:03 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:25:49 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

static int	get_nb_strings(char const *s, char c)
{
	int	i;
	int	nb_strings;

	i = 0;
	nb_strings = 1;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strings++;
			while (s[i] && s[i + 1] && s[i] == c)
				i++;
		}
		i++;
	}
	if (!s[0] || s[ft_strlen(s) - 1] == c)
		nb_strings--;
	return (nb_strings);
}

static int	get_index_next_string(char const *s, char c)
{
	static int	i = 0;

	while (s[i] && s[i] != c)
		i++;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static void	free_substr(char **substr, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(substr[i]);
		i++;
	}
}

static int	split_current_substr(char **result, const char *s,
		int current_substr, char c)
{
	int		s_index;
	char	*t;
	char	set[2];

	set[0] = c;
	set[1] = '\0';
	t = ft_strtrim(s, set);
	if (!t)
		return (-1);
	s_index = 0;
	if (current_substr > 0)
		s_index = get_index_next_string(t, c);
	result[current_substr] = ft_substr(t, s_index, ft_strchr(t + s_index, c)
			- (t + s_index));
	if (!result[current_substr])
	{
		free_substr(result, current_substr);
		free(t);
		return (-1);
	}
	free(t);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		nb_strings;
	int		current_substr;

	nb_strings = get_nb_strings(s, c);
	result = malloc(sizeof(char *) * (nb_strings + 1));
	current_substr = 0;
	if (!result)
		return (0);
	while (nb_strings >= current_substr + 1)
	{
		if (split_current_substr(result, s, current_substr, c) == -1)
		{
			free(result);
			return (0);
		}
		current_substr++;
	}
	result[current_substr] = NULL;
	return (result);
}
