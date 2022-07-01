#include "../builtins.h"

int	found_name(char **env, char *to_find)
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

int	len_env(char **env)
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

void	free_2d_tab(char ***tab)
{
	int	i;

	i = 0;
	if (*tab == NULL)
		return ;
	while (*tab[i])
	{
		free(*tab[i++]);
		*tab[i] = NULL;
	}
	free(*tab);
	*tab = NULL;
}

char	*ft_getenv(char **env, char *to_find)
{
	int		i;
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
