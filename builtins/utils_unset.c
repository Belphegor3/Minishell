int	found_unset_name_without_value(char **exp, char *to_find)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (exp[i])
	{
		j = 0;
		k = 0;
		if (to_find[k] && exp[i][j] == to_find[k])
		{
			while (exp[i][j] && exp[i][j] == to_find[k])
			{
				j++;
				k++;
			}
			if (!exp[i][j] && !to_find[k])
				return (i);
		}
		i++;
	}
	return (-1);
}

static char	**cpy_env_exp(char **env, char **cpy)
{
	int	i;

	i = 0;
	cpy = malloc(sizeof(char *) * (len_env(env) + 1));
	while (env[i])
	{
		cpy[i] = ft_strdup(env[i]);
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

int	display_unset_error(int error_count, char *to_export)
{
	ft_putstr_fd("minishell: unset: '", 1);
	ft_putstr_fd(to_export, 1);
	ft_putendl_fd("': not a valid identifier", 1);
	error_count++;
	return (error_count);
}
