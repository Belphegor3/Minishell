/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:10:54 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:10:55 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"

extern int g_status;

typedef struct s_redirections
{
	int	fdin;
	int	fdout;
	int	pipefd[2];
}t_redirections;

typedef struct s_as_tree_node
{
	int						type;
	char					*sz_data;
	struct s_as_tree_node	*left;
	struct s_as_tree_node	*right;
}	t_as_tree_node;

typedef struct s_tab
{
	char	**env;
	char	**exp;
}	t_tab;

int		execute_simple_command(t_syntax_node *tree_root,
			t_syntax_node *command_tree, t_redirections *redirect,
			t_tab *tabs);
void	close_standard_fds(void);
#endif
