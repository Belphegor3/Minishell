#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int	found_export_name_with_value(char **exp, char *to_find)
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

static char	**cpy_env_extend(char **env, char **to_export)
{
	int		i;
	int		j;
	char	**cpy_env_extended;

	i = 0;
	while (to_export[i])
		i++;
	j = 0;
	while (env[j])
		j++;
	cpy_env_extended = malloc(sizeof(char *) * (i + j + 1));
	if (!cpy_env_extended)
		return (NULL);
	i = 0;
	while (env[i])
	{
		cpy_env_extended[i] = strdup(env[i]);
		i++;
	}
	cpy_env_extended[i] = 0;
	return (cpy_env_extended);
}

char	*ft_strdup_export(char *src, int i, int j)
{
	int		len;
	char	*str;

	len = 0;
	while (src[len])
		len++;
	str = malloc(sizeof(*str) * (len + 3));
	if (!str)
		return (NULL);
	while (i < len)
	{
		if (src[i] == '=' && src[i + 1])
		{
			i++;
			str[j++] = '=';
			str[j++] = '"';
		}
		if (src[i] == '=' && !src[i + 1])
			str[j++] = '"';
		str[j++] = src[i++];
		if (i == len && i != j)
			str[j] = '"';
	}
	str[j + 1] = '\0';
	return (str);
}
