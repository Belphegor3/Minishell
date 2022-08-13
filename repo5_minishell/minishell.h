/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:10:54 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/09 06:52:37 by jfoucher         ###   ########.fr       */
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
# include <linux/limits.h>
# include <string.h>
# include <signal.h>
# include "libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include <sys/wait.h>
# include <sys/types.h>

extern int	g_status;

typedef struct s_redirections
{
	int	fdin;
	int	fdout;
	int	pipein[2];
	int	pipeout[2];
	int	save_fdin;
	int	save_fdout;
}	t_redirections;

typedef struct s_tab
{
	char	**env;
	char	**exp;
}	t_tab;

int		execute_simple_command(t_syntax_node **tree_root,
			t_syntax_node *command_tree, t_tab *tabs,
			t_redirections *redirect);
void	close_standard_fds(void);
int		check_for_unexpected_token(t_dlist *token_list);
void	handle_non_interactiv_signals(int signum);
void	handle_interactiv_signals(int signum);

#endif
