#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

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

static int	found_name_without_value(char **exp, char *to_find)
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

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (n > i)
		((char *)s)[i++] = 0;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	result = malloc(nmemb * size);
	if (result)
		ft_bzero(result, nmemb * size);
	return (result);
}

static int	len_env(char **env)
{
	int	i;

	i = 0;
	// if (!env)
	// 	return (0);
	// if (!env[i])
	// 	return (0);
	while (env[i])
	{
		// printf("debug : %s\n", env[i]);
		i++;
	}
	return (i);
}

static char	*ft_strdup(char *src);

static char	**cpy_env_exp(char **env)
{
	int	i;
	char	**cpy = NULL;

	i = 0;
	cpy = malloc(sizeof(char *) * (len_env(env) + 1));
	// cpy = ft_calloc(sizeof(char *) * (len_env(env) + 1), PATH_MAX);
	
	//printf("value of len_env : %d\n", len_env(env));
	
	while (env[i])
	{
		cpy[i] = ft_strdup(env[i]);
		i++;
	}
	
	cpy[i] = '\0';
	return (cpy);
}

/*											au dessus d ici c est dans les utils											*/
/*											au dessus d ici c est dans les utils											*/
/*											au dessus d ici c est dans les utils											*/
/*											au dessus d ici c est dans les utils											*/
/*											au dessus d ici c est dans les utils											*/
/*											au dessus d ici c est dans les utils											*/

// libft
/****************************************************************************************************************************/

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

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	// if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	// 	return (EXIT_SUCCESS);
	// return (EXIT_FAILURE);
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

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

// libft
/****************************************************************************************************************************/

int	display_unset_error(int error_count, char *to_export)
{
	ft_putstr_fd("minishell: unset: '", 1);
	ft_putstr_fd(to_export, 1);
	ft_putendl_fd("': not a valid identifier", 1);
	error_count++;
	return (error_count);
}

static int	check_args(char **to_export, int j)
{
	int	error_count;
	int	i;

	error_count = 0;
	while (to_export[j])
	{
		if (ft_isalpha(to_export[j][0]) == EXIT_SUCCESS && to_export[j][0] != '_')
		{
			error_count = display_unset_error(error_count, to_export[j++]);
			continue ;
		}
		i = -1;
		while (to_export[j][++i])
		{
			if (ft_isalnum(to_export[j][i]) == EXIT_SUCCESS && to_export[j][i] != '_')
			{	
				error_count = display_unset_error(error_count, to_export[j]);
				break ;
			}
		}
		j++;
	}
	return (error_count);
}

// void	free_2d_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 		free(tab[i++]);
// 	free(tab);
// }

int	execute_builtin_unset(char ***env, char ***exp, char **unset)
{
	int		j;
	int		k;
	char	**cpy_env;
	char	**cpy_exp;
	char	**final_env;
	char	**final_exp;

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
		cpy_env = cpy_env_exp(*env);
		final_env = cpy_env_exp(*env);
		j = found_name(final_env, unset[k]);
		if (j != -1)
		{
			while (final_env[++j])
				final_env[j - 1] = cpy_env[j];
			final_env[j - 1] = 0;
			*env = final_env;
		}
		cpy_exp = cpy_env_exp(*exp);
		final_exp = cpy_env_exp(*exp);
		j = found_name_without_value(final_exp, unset[k]);
		if (j != -1)
		{
			while (final_exp[++j])
				final_exp[j - 1] = cpy_exp[j];
			final_exp[j - 1] = 0;
			*exp = final_exp;
		}
		cpy_exp = cpy_env_exp(*exp);
		final_exp = cpy_env_exp(*exp);
		j = found_name(final_exp, unset[k]);
		if (j != -1)
		{
			while (final_exp[++j])
				final_exp[j - 1] = cpy_exp[j];
			final_exp[j - 1] = 0;
			*exp = final_exp;
		}
		k++;
	}
	// free_2d_tab(cpy_env);
	// free_2d_tab(cpy_exp);
	// free_2d_tab(final_env);
	// free_2d_tab(final_exp);
	return (EXIT_SUCCESS);
}

/* maintenant ca fonctionne mais il ne faut rien renvoyer juste changer l adresse des valeurs de env et export	*/
/* le prototype doit etre: void	execute_builtin_unset(char **env, char **exp, char **unset)						*/
/* reste a proteger, enlever les leaks aussi et mettre a la norme 												*/ 

// int	main(int ac, char **ag, char **env)
// {
// 	if (!execute_builtin_unset(&env, &ag, ag))
// 		for (int i = 0; env[i] != NULL; i++)
// 			printf("%s\n", env[i]);
// 	return 0;
// }
