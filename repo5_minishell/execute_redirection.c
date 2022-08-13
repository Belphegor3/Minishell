/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 04:02:16 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/12 04:16:03 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executor.h"

static int	get_flags(enum e_token_type type)
{
	int	flags;

	if (type == GREAT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (type == GREATGREAT)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_RDONLY;
	return (flags);
}

static int	get_newfd(enum e_token_type type)
{
	int	newfd;

	if (type == GREAT)
		newfd = STDOUT_FILENO;
	else if (type == GREATGREAT)
		newfd = STDOUT_FILENO;
	else
		newfd = STDIN_FILENO;
	return (newfd);
}

int	execute_redirection(t_syntax_node *command_tree)
{
	char	*pathname;
	int		oldfd;
	int		newfd;
	int		flags;

	flags = get_flags(command_tree->token->type);
	newfd = get_newfd(command_tree->token->type);
	pathname = command_tree->left->token->value->buffer;
	oldfd = open(pathname, flags, 0644);
	if (oldfd == -1)
	{
		perror("minishell: invalid_file");
		g_status = 1;
		return (-1);
	}
	dup2(oldfd, newfd);
	close(oldfd);
	if (command_tree->right)
		return (execute_redirection(command_tree->right));
	return (0);
}
