#include <limits.h>
#include <stdlib.h>

int	execute_builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		return (ft_putendl_fd(buf, 1) , EXIT_SUCCESS);
	return (EXIT_FAILURE);
}





// static int	found_name(char **env, char *to_find)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = 0;
// 	while (env[i])
// 	{
// 		j = 0;
// 		k = 0;
// 		if (env[i][j] == to_find[k])
// 		{
// 			while (env[i][j] == to_find[k++] && env[i][j] != '=')
// 				j++;
// 			if (env[i][j] == '=' && !to_find[k])
// 				return (i);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

// char	*execute_builtin_pwd_bis(char **env)
// {
// 	int	i;
// 	int	j;
// 	int	k;
// 	char	buf[PATH_MAX];

// 	i = found_name(env, "PWD");
// 	j = 4;
// 	k = 0;
// 	while (env[i][++j])
// 	{
// 		buf[k++] = env[i][j];
// 	}
// 	buf[k] = 0;
// 	return (buf);
// }

/* stupide si on unset PWD mais peut servir pour cd idk*/