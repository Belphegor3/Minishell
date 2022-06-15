#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int	found_name(char **env, char *to_find)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (env[i])
	{
		j = 0;
		k = 0;
		if (env[i][j] == to_find[k])
		{
			while (env[i][j] == to_find[k] && env[i][j] != '=')
			{
				j++;
				k++;
			}
			if (env[i][j] == '=' && !to_find[k])
				return (i);
		}
		i++;
	}
	return (-1);
}

static int	found_name_with_value(char **exp, char *to_find)
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
			if ((exp[i][j] == '=' && to_find[k] == '=') || (!exp[i][j] && to_find[k] == '='))
				return (i);
		}
		i++;
	}
	return (-1);
}

//	libft
/*****************************************************************************************************************************************/

static char	*ft_strdup(char *src)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	len = 0;
	while (src[len])
		len++;
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		str[j++] = src[i++];
	}
	str[j] = '\0';
	return (str);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

static void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

//	libft
/*****************************************************************************************************************************************/

static char	**cpy_env_extend(char **env, char **to_export)
{
	int		i;
	int		j;
	char	**cpy_env_ex;

	i = 0;
	while (to_export[i])
		i++;
	j = 0;
	while (env[j])
		j++;
	cpy_env_ex = malloc(sizeof(char *) * (i + j + 1));
	if (!cpy_env_ex)
		return (NULL);
	i = 0;
	while (env[i])
	{
		cpy_env_ex[i] = strdup(env[i]);
		i++; 
	}
	cpy_env_ex[i] = 0;
	return (cpy_env_ex);
}

static int	len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	display(char **display)
{
	int	i;

	i = 0;
	while (display[i])
		ft_putendl_fd(display[i++], 1);
}

static int	check_args(char **to_export, char **exp)
{
	int	j;
	int	error_count;

	if (!to_export)
		return (display(exp), EXIT_FAILURE);
	error_count = 0;
	j = 1;
	while (to_export[j])
	{
		if (!((to_export[j][0] >= 'a' && to_export[j][0] <= 'z') ||
			(to_export[j][0] >= 'A' && to_export[j][0] <= 'Z') ||
				to_export[j][0] == '_'))
		{
			ft_putstr_fd("minishell: export: '", 1);
			ft_putstr_fd(to_export[j], 1);
			ft_putendl_fd("': not a valid identifier", 1);
			error_count++;
		}
		j++;
	}
	if (error_count > 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*ft_strdup_export(char *src, int i, int j)
{
	int		len;
	char	*str;

	len = 0;
	while (src[len])
		len++;
	str = malloc(sizeof(*str) * (len + 3));
	if (!str)
		return (NULL);
	while (i < len)
	{
		if (src[i] == '=' && src[i + 1])
		{
			i++;
			str[j++] = '=';
			str[j++] = '"';
		}
		if (src[i] == '=' && !src[i + 1])
			str[j++] = '"';
		str[j++] = src[i++];
		if (i == len && i != j)
			str[j] = '"';
	}
	str[j + 1] = '\0';
	return (str);
}

int	execute_builtin_export(char ***env, char ***exp, char **to_export)
{
	int		index[4];
	char	**cpy_env_ex;
	char	**cpy_exp_ex;

	if (check_args(to_export, *exp))
		return (EXIT_FAILURE);
	index[0] = len_env(*env);
	index[3] = len_env(*exp);
	cpy_env_ex = cpy_env_extend(*env, to_export);
	cpy_exp_ex = cpy_env_extend(*exp, to_export);/* free cpy_env si cpy_exp fail */
	index[1] = 1;
	while (to_export[index[1]])
	{
		index[2] = 0;
		if ((to_export[index[1]][0] == '_' && !to_export[index[1]][1]) || (to_export[index[1]][0] == '_' && to_export[index[1]][1] == '=') || found_name(*exp, to_export[index[1]]) != -1)
		{
			index[1]++;
			continue ;
		}
		else if (found_name_with_value(*exp, to_export[index[1]]) != -1)
		{
			if (!execute_builtin_unset(env, exp, *to_export[index[1]]))						/*	limite fonction norm ta mere	*/
				return (EXIT_FAILURE);
			cpy_exp_ex[index[3]++] = ft_strdup_export(to_export[index[1]], 0, 0);
			cpy_env_ex[index[0]++] = ft_strdup(to_export[index[1]]);
		}
		else
		{
			while (to_export[index[1]][index[2]])
			{
				if (to_export[index[1]][index[2]] == '=')
					break ;
				index[2]++;
			}
			if (to_export[index[1]][index[2]] == '=')
				cpy_env_ex[index[0]++] = ft_strdup(to_export[index[1]]);
			cpy_exp_ex[index[3]++] = ft_strdup_export(to_export[index[1]], 0, 0);
		}
		index[1]++;
	}
	*env = cpy_env_ex;
	*exp = cpy_exp_ex;
	return (EXIT_SUCCESS);
}

/* fonctionne mais il ne faut rien renvoyer juste changer l adresse des valeurs de env et export	*/
/* le prototype doit etre: void	execute_builtin_export(char **env, char **exp, char **to_export)	*/
/* reste a proteger, enlever les leaks aussi et mettre a la norme 									*/ 

// int	main(int ac, char **ag, char **env)
// {
// 	// char	**lala;
// 	// char	**result;
// 	char	**ex = malloc(sizeof(char *));
// 	*ex = NULL;

// 	// lala = env;
// 	(void)ac;
// 	execute_builtin_export(&env, &ex, ag);
// 	// for (int j = 0; lala[j] != NULL; j++)
// 	// 	printf("%s\n", lala[j]);
// 	// printf("\n\n\n\n\n\n");
// 	for (int i = 1; ex[i] != NULL; i++)
// 		printf("%s\n", ex[i]);
// 	// for (int i = 0; result[i] != NULL; i++)
// 	// 	printf("%s\n", result[i]);
// 	return (0);
// }

// int	main(int ac, char **ag, char **env)
// {
// 	if (!execute_builtin_export(&env, &ag, ag))
// 	{	
// 		for (int i = 0; env[i] != NULL; i++)
// 			printf("%s\n", env[i]);
// 		printf("\nenv au dessus\n\n\n\n\n\n\n\n\n\nexport en dessous\n\n");
// 		for (int i = 0; ag[i] != NULL; i++)
// 			printf("%s\n", ag[i]);
// 	}
// 	return 0;
// }