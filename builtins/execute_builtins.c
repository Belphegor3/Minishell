#include "minishell.h"
#include "builtins.h"

int	execute_builtins(char **argv, t_tab *tabs)
{
	if (!ft_strcmp(argv[0], "echo"))
		execute_builtin_echo(argv);
    if (!ft_strcmp(argv[0], "pwd"))
		execute_builtin_pwd();
	if (!ft_strcmp(argv[0], "exit"))
		execute_builtin_exit(argv, tabs);
	if (!ft_strcmp(argv[0], "unset"))
		execute_builtin_unset(tabs, argv);
	if (!ft_strcmp(argv[0], "export"))
		execute_builtin_export(tabs, argv);
	if (!ft_strcmp(argv[0], "env"))
		execute_builtin_env(tabs->env);
	if (!ft_strcmp(argv[0], "cd"))
		execute_builtin_cd(argv, tabs);
	return (127);  
}
