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

int	execute_builtin_unset(t_tab *tabs, char **unset)
{
	int		j;
	int		k;
	char	**cpy_env = NULL;
	char	**cpy_exp = NULL;
	char	**final_env = NULL;
	char	**final_exp = NULL;

	if (check_args(unset, 1))
		return (EXIT_FAILURE);
	k = 1;
	while (unset[k])
	{
		if (unset[k][0] == '_' && !unset[k][1])
		{
			k++;
			continue ;
		}
		// if (cpy_env && final_env)
		// {
		// 	free_2d_tab(cpy_env);
		// 	free_2d_tab(final_env);
		// }
		cpy_env = cpy_env_exp(tabs->env, cpy_env);
		final_env = cpy_env_exp(tabs->env, final_env);
		j = found_name(final_env, unset[k]);
		if (j != -1)
		{
			while (final_env[++j])
				final_env[j - 1] = cpy_env[j];
			final_env[j - 1] = 0;
			free_2d_tab(&tabs->env);
			tabs->env = final_env;
			// free_2d_tab(final_env);
		}
		// if (cpy_exp && final_exp)
		// {
		// 	free_2d_tab(cpy_exp);
		// 	free_2d_tab(final_exp);
		// }
		cpy_exp = cpy_env_exp(tabs->exp, cpy_exp);
		final_exp = cpy_env_exp(tabs->exp, final_exp);
		j = found_unset_name_without_value(final_exp, unset[k]);
		if (j != -1)
		{
			while (final_exp[++j])
				final_exp[j - 1] = cpy_exp[j];
			final_exp[j - 1] = 0;
			free_2d_tab(&tabs->exp);
			tabs->exp = final_exp;
			// free_2d_tab(final_exp);
		}
		j = found_name(final_exp, unset[k]);
		if (j != -1)
		{
			while (final_exp[++j])
				final_exp[j - 1] = cpy_exp[j];
			final_exp[j - 1] = 0;
			free_2d_tab(&tabs->exp);
			tabs->exp = final_exp;
			// free_2d_tab(final_exp);
		}
		k++;
	}
	// free_2d_tab(cpy_env);
	// free_2d_tab(cpy_exp);
	// free_2d_tab(final_env);
	// free_2d_tab(final_exp);
	return (EXIT_SUCCESS);
}

// int	execute_builtin_unset(char ***env, char ***exp, char **unset)
// {
// 	int		j;
// 	int		k;

// 	if (check_args(unset, 1))
// 		return (EXIT_FAILURE);
// 	k = 0;
// 	while (unset[k])
// 	{
// 		if (unset[k][0] == '_' && !unset[k][1])
// 		{
// 			k++;
// 			continue ;
// 		}
// 		j = found_name(*env, unset[k]);
// 		if (j != -1)
// 		{
// 			while (*env[j])
// 			{
// 				*env[j] = *env[j + 1];
// 				j++;
// 			}
// 			*env[j] = 0;
// 		}
// 		j = found_unset_name_without_value(*exp, unset[k]);
// 		if (j != -1)
// 		{
// 			while (*exp[j])
// 			{
// 				*exp[j] = *exp[j + 1];
// 				j++;
// 			}
// 			*exp[j] = 0;
// 		}
// 		j = found_name(*exp, unset[k]);
// 		if (j != -1)
// 		{
// 			while (*exp[j])
// 			{
// 				*exp[j] = *exp[j + 1];
// 				j++;
// 			}
// 			*exp[j] = 0;
// 		}
// 		k++;
// 	}
// 	/*free_2d_tab(cpy_env);
// 	 *free_2d_tab(cpy_exp);
// 	 *free_2d_tab(final_env);
// 	 *free_2d_tab(final_exp);*/
// 	return (EXIT_SUCCESS);
// }

