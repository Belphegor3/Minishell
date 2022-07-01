/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:10:44 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:10:45 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"
# include "minishell.h"
# include "builtins.h"

char	*get_filepath(char *pathname, char **env);
void	execute_job(t_syntax_node *tree_root, t_syntax_node *command_tree,
			t_redirections *redirect, t_tab *tabs);
void	executor(t_syntax_node *command_tree, t_tab *tabs);
#endif
