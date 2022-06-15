#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

//	libft
/*************************************************************************************************************************/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

//	libft
/*************************************************************************************************************************/

// char	*remove_name(char *path)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (path[i])
// 	{
// 		if (path[i] == '=')
// 			break ;
// 		i++;
// 	}
// 	while (path[i])
// 	{
// 		path[j] = path[i + j];
// 		i++;
// 		j++;
// 	}
// 	path[j] = 0;
// 	return (path);
// }

int	execute_builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		return (ft_putendl_fd(buf, 1), EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	can_i_access(char *path)
{
	if (access(path, F_OK))
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

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
		if (env[i][j] == to_find[k])									/*	utils	*/
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

static char	*ft_getenv(char **env, char *to_find)
{
	int	i;
	int		j;
	int		k;
	char	*path;

	i = found_name(env, to_find);
	if (i == -1)
		return (NULL);
	path = malloc(PATH_MAX + 1);
	if (!path)
		return (printf("\e[2;5;30;101mMalloc path failed\e[0m\n"), NULL);
	j = 0;
	while (env[i][j])
		if (env[i][j++] == '=')
			break ;
	k = 0;
	while (env[i][j])
		path[k++] = env[i][j++];
	path[k] = 0;
	return (path);
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
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	deal_with_oldpwd(char ***env, char ***exp)
{
	char	**to_export;
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
	{
		to_export = malloc(sizeof(char *) * 2);
		to_export[0] = malloc(7 + 1 + ft_strlen(buf));
		to_export[1] = malloc(1);
		to_export[0][0] = 0;
		to_export[0] = strcat(to_export[0], "OLDPWD");
		to_export[1][0] = 0;
		execute_builtin_unset(env, exp, to_export);
		to_export[0] = strcat(to_export[0], "=");
		to_export[0] = strcat(to_export[0], buf);
		execute_builtin_export(env, exp, to_export);
		// free_2d_tab(to_export);
	}
	return ;
}

int	execute_builtin_cd(char **to_cd, char ***env, char ***exp)
{
	char	*path;
	int		i;

	deal_with_oldpwd(env, exp);
	i = 0;
	if (to_cd[1] && to_cd[1][0] == '\0')
		return (EXIT_SUCCESS);
	if (check_args(to_cd, *env))
		return (EXIT_FAILURE);
	if (can_i_access(to_cd[1]))
		return (EXIT_FAILURE);
	if (chdir(to_cd[1]))
		printf("minishell: cd: %s: Not a directory\n", to_cd[1]);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	int	i;

	(void)ac;
	execute_builtin_pwd();
	for (int j = 0; env[j] != NULL; j++)
			printf("%s\n", env[j]);
	i = execute_builtin_cd(av, &env, &av);
	execute_builtin_pwd();
	for (int k = 0; env[k] != NULL; k++)
			printf("%s\n", env[k]);
	return (0);
}

/*	reste a mettre en place les variables d environnement PWD, OLDPWD et CDPATH					*/
/*	donc a la place de faire des chdir il me faut une fonction qui va gerer les PWD				*/
/*	il faut aussi changer le getenv et parcourir l env qu on doit plutot envoyer en parametre	*/
/*	un vieux ft_strcmp devrait suffire															*/
