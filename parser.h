/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:10:59 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:11:04 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

enum e_node_type
{
	JOB,
	COMMAND,
	SIMPLE_COMMAND,
	REDIRECTION,
	PATHNAME,
	TOKEN_LIST,
	TOKEN,
	FILENAME
};

typedef struct s_syntax_node
{
	enum e_node_type		type;
	t_token					*token;
	struct s_syntax_node	*left;
	struct s_syntax_node	*right;
}t_syntax_node;

t_syntax_node	*create_node(void);
void			delete_syntax_tree(t_syntax_node *root);
t_syntax_node	*parse_simple_command(t_tok_list **token, char **envp);
t_syntax_node	*parser(t_tok_list *token, char **envp);
#endif
