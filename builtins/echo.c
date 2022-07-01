#include "../builtins.h"

static int	erase_n(char *args)
{
	int	i;

	i = 0;
	if (args[i] == '-' && args[i + 1])
	{
		i++;
		while (args[i])
		{
			if (args[i] != '\0' && args[i] != 'n')
				return (EXIT_SUCCESS);
			i++;
		}
	}
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static void	echo_itself(char **args, int *newline)
{
	int	size;
	int	i;

	i = 1;
	size = len_env(args);
	while (args[i])
	{
		if (erase_n(args[i]) && i < size)
		{
			i++;
			*newline = 0;
		}
		else
			break ;
	}
	if (args[i])
	{
		while (args[i] && i < size)
		{
			ft_putstr_fd(args[i], 1);
			if (i < (size - 1))
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
}

int	execute_builtin_echo(char **args)
{
	int	newline;

	newline = 1;
	if (args[1])
		echo_itself(args, &newline);
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
