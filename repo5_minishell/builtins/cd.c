/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:53:31 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 14:53:32 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (i == 1)
	{
		if (found_name_without_value(env, "HOME") != -1)
			return (EXIT_FAILURE);
		path = ft_getenv(env, "HOME");
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		else
		{
			if (chdir(path))
				strerror(errno);
			return (free(path), EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	chdir_not_found(void)
{
	write(2, "chdir: error retrieving current directory: getcwd:", 51);
	write(2, " cannot access parent directories: No such file or ", 52);
	write(2, "directory\nbash: cd: ..: Stale file handle\n", 43);
}

char	*path_using_chdir(char *path)
{
	int		i;
	char	*chdirable;

	i = 0;
	chdirable = malloc(ft_strlen(path) + 1);
	if (!chdirable)
		return (NULL);
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
	char	*path;

	if (to_cd[1] && to_cd[1][0] == '\0')
		return (EXIT_SUCCESS);
	if (check_args(to_cd, tabs->env))
		return (EXIT_FAILURE);
	if (to_cd[1] && access(to_cd[1], F_OK))
		return (perror("minishell: cd"), EXIT_FAILURE);
	path = path_using_chdir(to_cd[1]);
	if (!path)
		return (printf("Malloc failed, can't get the path\n"), EXIT_FAILURE);
	if (chdir(path) == -1)
	{
		free(path);
		strerror(errno);
	}
	free(path);
	return (EXIT_SUCCESS);
}
