/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:08:58 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/12 05:24:11 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "builtins.h"

void	ft_perror(char *command_name, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

static char	*ft_strjoin_with_slash(char *s1, char *s2)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, "/");
	result = ft_strjoin(tmp, s2);
	free(tmp);
	return (result);
}

static char	*check_executable_path(char *filepath)
{
	struct stat	statbuf;

	stat(filepath, &statbuf);
	if (access(filepath, F_OK))
	{
		ft_perror(filepath, strerror(errno));
		g_status = 127;
	}
	else if (!S_ISREG(statbuf.st_mode))
	{
		ft_perror(filepath, strerror(EISDIR));
		g_status = 126;
	}
	else if (access(filepath, X_OK))
	{
		ft_perror(filepath, strerror(errno));
		g_status = 126;
	}
	else
		return (filepath);
	free(filepath);
	return (NULL);
}

static char	*look_for_path_in_env_variable(char *pathname, char *path)
{
	char	**patharray;
	char	*filepath;
	int		i;

	i = 0;
	patharray = ft_split(path, ':');
	while (patharray[i])
	{
		filepath = ft_strjoin_with_slash(patharray[i], pathname);
		if (access(filepath, X_OK) == 0)
			break ;
		free(filepath);
		filepath = NULL;
		i++;
	}
	if (!filepath)
	{
		ft_perror(pathname, "command not found");
		g_status = 127;
		free(filepath);
		filepath = NULL;
	}
	free_2d_tab(&patharray);
	return (filepath);
}

char	*get_filepath(char *pathname, char **env)
{
	char	*filepath;
	char	*path;

	filepath = ft_strdup(pathname);
	if (filepath[0] == '/' || (filepath[0] == '.' && filepath[1] == '/'))
		filepath = check_executable_path(filepath);
	else
	{
		path = ft_getenv(env, "PATH");
		if (!path)
			return (filepath);
		free(filepath);
		filepath = look_for_path_in_env_variable(pathname, path);
		free(path);
	}
	return (filepath);
}
