#include "../builtins.h"

static int	found_name_without_value(char **env, char *to_find)
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
			if (env[i][j] == '=' && env[i][j + 1] == '\0' && !to_find[k])
				return (i);
		}
		i++;
	}
	return (-1);
}

static int	check_args(char **to_cd, char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (to_cd[i])
		i++;
	if (i > 2)
		return (printf("minishell: cd: too many arguments\n"), EXIT_FAILURE);
	if (i == 1)
	{
		if (found_name_without_value(env, "HOME") != -1)
			return (EXIT_FAILURE);
		path = ft_getenv(env, "HOME");
		if (!path)
			return (printf("minishell: cd: HOME not set\n"), EXIT_FAILURE);
		else
		{
			if (chdir(path))
				printf("minishell: cd: %s: Not a directory\n", path);
			return (free(path), EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	chdir_not_found(void)
{
	write(1, "chdir: error retrieving current directory: getcwd:", 51);
	write(1, " cannot access parent directories: No such file or ", 52);
	write(1, "directory\nbash: cd: ..: Stale file handle\n", 43);
}

char	*path_using_chdir(char *path)
{
	int	i;
	char	*chdirable;

	i = 0;
	chdirable = malloc(ft_strlen(path) + 1);
	while (path[i])
	{
		chdirable[i] = path[i];
		i++;
	}
	chdirable[i] = 0;
	return (chdirable);
}

int	execute_builtin_cd(char **to_cd, t_tab *tabs)
{
	char	*former_pwd_path;

	former_pwd_path = ft_getenv(tabs->env, "PWD");
	if (to_cd[1] && to_cd[1][0] == '\0')
		return (EXIT_SUCCESS);
	if (check_args(to_cd, tabs->env))
		return (EXIT_FAILURE);
	if (access(to_cd[1], F_OK))
		return (printf("minishell: cd: %s: No such file or directory\n",
				to_cd[1]), EXIT_FAILURE);
	if (chdir(path_using_chdir(to_cd[1])) == -1)
		printf("minishell: cd: %s: Not a directory\n", to_cd[1]);
	// else
	// 	return (chdir_not_found(), EXIT_FAILURE);
	// if (deal_with_oldpwd(env, exp, former_pwd_path))
	// 	;
	free(former_pwd_path);
	// if (deal_with_pwd(env, exp))
	// 	;
	return (EXIT_SUCCESS);
}
