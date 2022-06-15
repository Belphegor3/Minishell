#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*get_filepath(char *pathname, char **envp)
{
	(void)envp;
	char	*filepath;
	char	*path;
	char	**patharray;
	int		i;
	char	*tmp;

	i = 0;
	path = getenv("PATH");
	filepath = ft_strdup(pathname);
	if (access(filepath, R_OK) == -1)
	{
		free(filepath);
		patharray = ft_split(path, ':');
		while (patharray[i])
		{
			tmp = ft_strjoin(patharray[i], "/");
			filepath = ft_strjoin(tmp, pathname);
			free(tmp);
			if (access(filepath, R_OK) == 0)
				break;
			free(filepath);
			i++;
		}
		i = 0;
		while (patharray[i])
		{
			free(patharray[i]);
			i++;
		}
		free(patharray);
	}
	return (filepath);
}
