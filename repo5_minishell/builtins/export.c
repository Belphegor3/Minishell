/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:54:09 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 14:54:10 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

static int	check_args(char **to_export, t_tab *tabs, int j, int error_count)
{
	int	i;

	if (to_export[0] && !to_export[1])
		return (display(tabs->exp), EXIT_FAILURE);
	while (to_export[j])
	{
		if (ft_isalpha(to_export[j][0]) == EXIT_SUCCESS &&
			to_export[j][0] != '_')
		{
			error_count = display_export_error(error_count, to_export[j++]);
			continue ;
		}
		i = -1;
		while (to_export[j][++i] && to_export[j][i] != '=')
		{
			if (ft_isalnum(to_export[j][i]) == EXIT_SUCCESS &&
				to_export[j][i] != '_'/* && to_export[j][i] != '='*/)
			{	
				error_count = display_export_error(error_count, to_export[j]);
				break ;
			}
		}
		j++;
	}
	return (error_count);
}

static void	change_value(char **to_change, char *to_export)
{
	int	i;

	i = 0;
	while (to_export[i])
	{
		(*to_change)[i] = to_export[i];
		i++;
	}
	(*to_change)[i] = '\0';
}

static int	name_with_value(t_tab *tabs, char *to_export, int *index)
{
	char	*to_free;
	int		i;

	i = found_export_name_with_value(tabs->exp, to_export);
	if (i != -1)
	{
		change_value(&tabs->exp[i], to_export);
		to_free = to_find(to_export);
		if (!to_free)
			return (EXIT_FAILURE);
		if (found_name(tabs->env, to_free) != -1)
			change_value(&tabs->env[i], to_export);
		else
			tabs->env[*index++] = ft_strdup(to_export);
		free(to_free);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static void	no_name_yet(t_tab *tabs, char *to_export, int *index0, int *index3)
{
	int	i;

	i = 0;
	while (to_export[i])
	{
		if (to_export[i] == '=')
			break ;
		i++;
	}
	if (to_export[i] == '=')
		tabs->env[*index0] = ft_strdup(to_export);
	tabs->exp[*index3] = ft_strdup(to_export);
}

int	execute_builtin_export(t_tab *tabs, char **to_export)
{
	int		index[4];

	if (check_args(to_export, tabs, 1, 0))
		return (EXIT_FAILURE);
	index[1] = 1;
	while (to_export[index[1]])
	{
		index[0] = len_env(tabs->env);
		index[3] = len_env(tabs->exp);
		index[2] = 0;
		if (found_name(tabs->exp, to_export[index[1]]) != -1)
		{
			index[1]++;
			continue ;
		}
		if (name_with_value(tabs, to_export[index[1]], &index[0]) == 1)
			no_name_yet(tabs, to_export[index[1]], &index[0], &index[3]);
		index[0]++;
		index[3]++;
		tabs->env[index[0]++] = NULL;
		tabs->exp[index[3]++] = NULL;
		index[1]++;
	}
	return (EXIT_SUCCESS);
}
