#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"

typedef struct	s_redirections
{
	int	fdin;
	int	fdout;
	int pipefd[2];
}t_redirections;

void	execute_builtin_echo(t_syntax_node *token_list);
char	*get_filepath(char *pathname, char **envp);
void	executor(t_syntax_node *command_tree, char **envp);
#endif
