/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:10:50 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/05 10:24:37 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft/libft.h"

enum	e_token_type
{
	WORD,
	PIPE,
	GREAT,
	LESS,
	GREATGREAT
};

typedef struct s_token
{
	enum e_token_type	type;
	t_vector			*value;
}t_token;

t_token		*get_token(t_dlist *elem);
t_dlist		*lexer(char *line);
void		destroy_token(t_token *token);
t_token		*create_token(enum e_token_type type);
t_token		*take_greatgreat(char **iter);
t_token		*take_great(char **iter);
t_token		*take_less(char **iter);
void		take_single_quote(t_token *token, char **iter);
void		take_quoted_dollar(t_token *token, char **iter);
void		take_double_quote(t_token *token, char **iter);
t_token		*take_redirection(char **iter);
#endif
