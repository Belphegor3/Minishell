#include "minishell.h"
#include "../builtins.h"
#include "libft.h"

int	execute_builtin_exit(char **argv, t_tab *tabs)
{
	// unsigned int	status;

	// status = exit_status % 256;
	free_2d_tab(&tabs->env);
	free_2d_tab(&tabs->exp);
	if (argv[0])
		exit(ft_atoi(argv[0]));
	else
		exit(g_status);
	/*	si exit est un token il faut juste ft_putendl("exit"); et 
		mettre le exit status a 0
		sinon faut tout bien free si c pas deja fait et exit(1);
		SIGQUIT	131
		SIGINT	130
		command not found	127
		A file to be executed was found, but it was not an 
		executable utility.	126
		si tout se passe bien 0
		sinon >0 mais si >255 cest undefined behavior donc on modulo 256 donc
		on peut avoir un faux 0 comme si tout se passait bien	*/
}
