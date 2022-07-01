/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:08:41 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:08:44 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "minishell.h"

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
		argv[i] = command_tree->left->token->value->buffer;
		command_tree = command_tree->right;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}



int	is_a_builtin(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd")
			|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "export")
			|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "env")
			|| !ft_strcmp(command, "exit"))
		return (1);
	return (0);
}

int	execute_simple_command(t_syntax_node *tree_root,
		t_syntax_node *command_tree,
		t_redirections *redirect, t_tab *tabs)
{
	pid_t	pid;
	char	**argv;
	char	*filepath;

	argv = compose_argv(command_tree);
	if (is_a_builtin(argv[0]) && tree_root->right == NULL)
		return (execute_builtins(argv, tabs));
	pid = fork();
	if (pid == 0)
	{
		close(redirect->pipefd[0]);
		close(redirect->pipefd[1]);
		close(redirect->fdin);
		close(redirect->fdout);
		if (is_a_builtin(argv[0]))
			execute_builtins(argv, tabs);
		else
		{
			filepath = get_filepath(argv[0], tabs->env);
			execve(filepath, argv, tabs->env);
			ft_putstr_fd(argv[0], 2);
			ft_putendl_fd(": command not found", 2);
			close_standard_fds();
			free(argv);
			delete_syntax_tree(tree_root);
			exit (127);
		}
	}
	free(argv);
	return (0);
}
