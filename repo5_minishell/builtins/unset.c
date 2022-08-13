/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:54:18 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 14:54:19 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

static int	check_args(char **to_export, int j)
{
	int	error_count;
	int	i;

	error_count = 0;
	while (to_export[j])
	{
		if (ft_isalpha(to_export[j][0]) == EXIT_SUCCESS &&
			to_export[j][0] != '_')
		{
			error_count = display_unset_error(error_count, to_export[j++]);
			continue ;
		}
		i = -1;
		while (to_export[j][++i])
		{
			if (ft_isalnum(to_export[j][i]) == EXIT_SUCCESS &&
				to_export[j][i] != '_')
			{	
				error_count = display_unset_error(error_count, to_export[j]);
				break ;
			}
		}
		j++;
	}
	return (error_count);
}

static void	name_with_value(t_tab *tabs, char *unset)
{
	int	j;

	j = found_name(tabs->env, unset);
	if (j != -1)
	{
		free(tabs->env[j]);
		while (tabs->env[j])
		{
			tabs->env[j] = tabs->env[j + 1];
			j++;
		}
		tabs->env[j] = 0;
	}
}

static void	name_without_value(t_tab *tabs, char *unset)
{
	int	j;

	j = found_unset_name_without_value(tabs->exp, unset);
	if (j != -1)
	{
		free(tabs->exp[j]);
		while (tabs->exp[j])
		{
			tabs->exp[j] = tabs->exp[j + 1];
			j++;
		}
		tabs->exp[j] = 0;
	}
}

static void	exists_in_exp_but_not_in_env(t_tab *tabs, char *unset)
{
	int	j;

	j = found_name(tabs->exp, unset);
	if (j != -1)
	{
		free(tabs->exp[j]);
		while (tabs->exp[j])
		{
			tabs->exp[j] = tabs->exp[j + 1];
			j++;
		}
		tabs->exp[j] = 0;
	}
}

int	execute_builtin_unset(t_tab *tabs, char **unset)
{
	int		k;

	if (check_args(unset, 1))
		return (EXIT_FAILURE);
	k = 0;
	while (unset[k])
	{
		if (unset[k][0] == '_' && !unset[k][1])
		{
			k++;
			continue ;
		}
		name_with_value(tabs, unset[k]);
		name_without_value(tabs, unset[k]);
		exists_in_exp_but_not_in_env(tabs, unset[k]);
		k++;
	}
	return (EXIT_SUCCESS);
}
