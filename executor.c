#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "executor.h"
#include "minishell.h"
#include <stdio.h>

void	execute_job(t_syntax_node *command_tree, t_redirections *redirect, char **envp);

void	execute_redirection(t_syntax_node *command_tree)
{
	char	*pathname;
	int		fd;

	if (command_tree->token->type == GREAT)
	{
		pathname = malloc(sizeof(char) * (command_tree->left->token->slice.length + 1));
		assert(pathname);
		ft_strlcpy(pathname, command_tree->left->token->slice.start, command_tree->left->token->slice.length + 1);
		fd = open(pathname, O_CREAT | O_WRONLY, 0644);
		free(pathname);
		assert(fd != -1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (command_tree->token->type == GREATGREAT)
	{
		pathname = malloc(sizeof(char) * (command_tree->left->token->slice.length + 1));
		assert(pathname);
		ft_strlcpy(pathname, command_tree->left->token->slice.start, command_tree->left->token->slice.length + 1);
		fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0644);
		free(pathname);
		assert(fd != -1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (command_tree->token->type == LESS)
	{
		pathname = malloc(sizeof(char) * (command_tree->left->token->slice.length + 1));
		assert(pathname);
		ft_strlcpy(pathname, command_tree->left->token->slice.start, command_tree->left->token->slice.length + 1);
		fd = open(pathname, O_CREAT | O_RDONLY, 0644);
		free(pathname);
		assert(fd != -1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	execute_command(t_syntax_node *command_tree, t_redirections *redirect,
		char **envp)
{
	if (command_tree->right)
		execute_redirection(command_tree->right);
	execute_simple_command(command_tree->left, redirect, envp);
	dup2(redirect->fdout, STDOUT_FILENO);
}

void	execute_pipe(t_syntax_node *command_tree, t_redirections *redirect,
					char **envp)
{
	assert(pipe(redirect->pipefd) != -1);
	dup2(redirect->pipefd[1], STDOUT_FILENO);
	close(redirect->pipefd[1]);
	execute_command(command_tree->left, redirect, envp);
	dup2(redirect->fdout, STDOUT_FILENO);

	dup2(redirect->pipefd[0], STDIN_FILENO);
	close(redirect->pipefd[0]);
	execute_job(command_tree->right, redirect, envp);
	dup2(redirect->fdin, STDIN_FILENO);
	wait(NULL);
}

void	execute_job(t_syntax_node *command_tree, t_redirections *redirect,
					char **envp)
{

	if (command_tree->right == NULL)
	{
		execute_command(command_tree->left, redirect, envp);
		wait(NULL);
	}
	else
	{
		execute_pipe(command_tree, redirect, envp);
	}
}

void	executor(t_syntax_node *command_tree, char **envp)
{
	t_redirections	redirect;

	redirect.fdin = dup(STDIN_FILENO);
	redirect.fdout = dup(STDOUT_FILENO);
	redirect.pipefd[0] = -1;
	redirect.pipefd[1] = -1;
	execute_job(command_tree, &redirect, envp);
	dup2(redirect.fdin, STDIN_FILENO);
	dup2(redirect.fdout, STDOUT_FILENO);
	close(redirect.fdin);
	close(redirect.fdout);
}
