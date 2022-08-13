/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:54:33 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 14:54:34 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	found_export_name_with_value(char **exp, char *to_find)
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
			while (exp[i][j] && exp[i][j] == to_find[k] && to_find[k] != '=')
			{
				j++;
				k++;
			}
			if ((exp[i][j] == '=' && to_find[k] == '=') ||
				(!exp[i][j] && to_find[k] == '='))
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**cpy_env_extend(char **env, char **to_export)
{
	int		i;
	int		j;
	char	**cpy_env_extended;

	i = 0;
	if (to_export)
		while (to_export[i])
			i++;
	j = 0;
	while (env[j])
		j++;
	cpy_env_extended = malloc(sizeof(char *) * (i + j + 1));
	if (!cpy_env_extended)
		return (printf("\e[1;31Copy failed\n\e[0m"), NULL);
	i = 0;
	while (env[i])
	{
		cpy_env_extended[i] = ft_strdup(env[i]);
		if (!cpy_env_extended[i])
			return (free_2d_tab(&cpy_env_extended), NULL);
		i++;
	}
	cpy_env_extended[i] = 0;
	return (cpy_env_extended);
}

int	display_export_error(int error_count, char *error)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	error_count++;
	return (error_count);
}

char	*to_find(char *to_change)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc(ft_strlen(to_change) + 1);
	if (!res)
		return (printf("Malloc failed, can't change the value of %s\n",
				to_change), NULL);
	while (to_change[++i] != '=')
		res[i] = to_change[i];
	res[i] = 0;
	return (res);
}
