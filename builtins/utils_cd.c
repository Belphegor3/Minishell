#include "../builtins.h"

static char	*ft_strcat(char *dest, char *src)
{
	size_t	dest_len;
	size_t	i;

	i = 0;
	if (dest)
		dest_len = ft_strlen(dest);
	else
		return (src);
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

int	found_name_with_value(char **exp, char *to_find)
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
			while (to_find[k] && exp[i][j] && exp[i][j] == to_find[k])
			{
				j++;
				k++;
			}
			if ((exp[i][j] && (exp[i][j] == '=' && !to_find[k])) ||
				(!exp[i][j] && !to_find[k]))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	deal_with_oldpwd(t_tab *tabs, char *former_pwd_path)
{
	char	**to_change;

	if (found_name_with_value(tabs->env, "OLDPWD") == -1)
		return (EXIT_FAILURE);
	to_change = malloc(sizeof(char *) * 2);
	if (!to_change)
		return (printf("\e[30;101mOLDPWD n a pas ete mis a jour\e[0m"), 1);
	to_change[0] = malloc(PATH_MAX);
	if (!to_change[0])
		return (free(to_change),
			printf("\e[30;101mOLDPWD n a pas ete mis a jour\e[0m"), 1);
	to_change[0] = NULL;
	to_change[0] = ft_strcat(to_change[0], "OLDPWD");
	to_change[1] = NULL;
	if (former_pwd_path != NULL)
	{
		execute_builtin_unset(tabs, to_change);
		to_change[0] = ft_strcat(to_change[0], "=");
		to_change[0] = ft_strcat(to_change[0], former_pwd_path);
		free(former_pwd_path);
		execute_builtin_export(tabs, to_change);
	}
	else
		execute_builtin_unset(tabs, to_change);
	return (free_2d_tab(&to_change), EXIT_SUCCESS);
}

static void	fck_the_norm(char ***to_set)
{
	*to_set[0] = NULL;
	*to_set[1] = NULL;
}

int	deal_with_pwd(t_tab *tabs)
{
	char	buf[PATH_MAX];
	char	**to_change;

	if (found_name_with_value(tabs->env, "PWD") != -1)
	{
		if (getcwd(buf, PATH_MAX))
		{
			to_change = malloc(sizeof(char *) * 2);
			if (!to_change)
				return (printf("\e[1;31mPWD n a pas ete mis a jour\e[0m"), 1);
			to_change[0] = malloc(5 + ft_strlen(buf));
			if (!to_change[0])
				return (printf("\e[1;31mPWD n a pas ete mis a jour\e[0m"), 1);
			fck_the_norm(&to_change);
			// to_change[0] = NULL;
			// to_change[1] = NULL;
			to_change[0] = ft_strcat(to_change[0], "PWD");
			execute_builtin_unset(tabs, to_change);
			to_change[0] = ft_strcat(to_change[0], "=");
			to_change[0] = ft_strcat(to_change[0], buf);
			execute_builtin_export(tabs, to_change);
			free(to_change);
		}
		else
			return (pwd_not_found(), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
