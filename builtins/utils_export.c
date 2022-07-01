#include "../builtins.h"

int	found_export_name_with_value(char **exp, char *to_find)
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
			if ((exp[i][j] == '=' && to_find[k] == '=') ||
				(!exp[i][j] && to_find[k] == '='))
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**cpy_env_extend(char **env, char **to_export)
{
	int		i;
	int		j;
	char	**cpy_env_extended;

	i = 0;
	if (to_export)
		while (to_export[i])
			i++;
	j = 0;
	while (env[j])
		j++;
	cpy_env_extended = malloc(sizeof(char *) * (i + j + 1));
	if (!cpy_env_extended)
		return (printf("\e[1;31Copy failed\n\e[0m"), NULL);
	i = 0;
	while (env[i])
	{
		cpy_env_extended[i] = ft_strdup(env[i]);
		if (!cpy_env_extended[i])
			return (free_2d_tab(&cpy_env_extended), NULL);
		i++;
	}
	cpy_env_extended[i] = 0;
	return (cpy_env_extended);
}

char	*ft_strdup_export(char *src, int i, int j)
{
	char	*str;

	str = malloc(ft_strlen(src) + 3);
	if (!str)
		return (printf("\e[1;31Copy failed\n\e[0m"), NULL);
	while (src[i])
	{
		if (src[i] == '=')
			break ;
		str[j++] = src[i++];
	}
	if (src[i] == '=')
	{
		str[j++] = '=';
		str[j++] = '"';
		i++;
	}
	while (src[i])
		str[j++] = src[i++];
	if (i != j)
		str[j++] = '"';
	str[j] = '\0';
	return (str);
}
