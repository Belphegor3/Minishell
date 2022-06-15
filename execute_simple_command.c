#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "executor.h"

static int	count_arguments(t_syntax_node *token_list)
{
	int	nb_arguments;

	nb_arguments = 1;
	while (token_list)
	{
		nb_arguments++;
		token_list = token_list->right;
	}
	return (nb_arguments);
}

static char	**compose_argv(t_syntax_node *command_tree)
{
	int		i;
	char	**argv;
	int		nb_args;

	nb_args = count_arguments(command_tree->right) + 1;
	argv = malloc(sizeof(t_syntax_node) * (nb_args));
	i = 0;
	while (command_tree)
	{
		argv[i] = malloc(sizeof(char) * (command_tree->left->token->slice.length + 1));
		ft_strlcpy(argv[i], command_tree->left->token->slice.start,
				command_tree->left->token->slice.length + 1);
		command_tree = command_tree->right;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int	execute_simple_command(t_syntax_node *command_tree,
		t_redirections *redirect, char *envp[])
{
	pid_t	pid;
	char	**argv;

	// if (ft_strncmp("echo", command_tree->left->token->slice.start, command_tree->left->token->slice.length) == 0)
	// 	execute_builtin_echo(command_tree->right);
	// else
	// {
		pid = fork();
		if (pid == 0)
		{
			argv = compose_argv(command_tree);
			(void)redirect;
			close(redirect->pipefd[0]);
			close(redirect->pipefd[1]);
			close(redirect->fdin);
			close(redirect->fdout);
			execve(get_filepath(argv[0], envp), argv, envp);
		}
	// }
	return (0);
}
