#include <stdlib.h>
#include "minishell.h"
#include "expander.h"
#include <stdio.h>
#include "builtins.h"

static int	expand_exit_status(t_vector *word, int *iter)
{
	char	*string_value_of_exit_status;

	string_value_of_exit_status = ft_itoa(g_status);
	if (!string_value_of_exit_status)
		return (-1);
	ft_vecremove(word, (*iter), (*iter));
	ft_vecinsert(word, (*iter), string_value_of_exit_status,
			ft_strlen(string_value_of_exit_status) + 1);
	*iter += ft_strlen(string_value_of_exit_status);
	free(string_value_of_exit_status);
	return (0);
}

int	expand_variable(t_vector *word, int *iter, char **env)
{
	int			i;
	char		*variable;
	t_vector	name;

	i = (*iter);
	i++;
	if (((char*)word->buffer)[i] == '?')
		return (expand_exit_status(word, iter));
	name = ft_veccreate(2, sizeof(char));
	while (((char*)word->buffer)[i] != '\0'
			&& ft_isalnum(((char*)word->buffer)[i]) == 1)
	{
		ft_vecadd(&name, word->buffer + i);
		i++;
	}
	ft_vecadd(&name, "\0");
	variable = ft_getenv(env, name.buffer);
	ft_vecdestroy(&name);
	ft_vecremove(word, (*iter), i - 1);
	if (variable)
	{
		ft_vecinsert(word, (*iter), variable, ft_strlen(variable));
		(*iter) += ft_strlen(variable);
	}
	return (0);
}
