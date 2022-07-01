/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:10:50 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:10:51 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

enum	e_token_type
{
	WORD,
	QUOTE,
	DQUOTE,
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

typedef struct s_tok_list
{
	t_token				*token;
	struct s_tok_list	*next;
}t_tok_list;

t_tok_list	*ft_toklstnew(t_token *token);
t_tok_list	*ft_toklstlast(t_tok_list *lst);
void		ft_toklst_clear(t_tok_list **lst, void (*del)(void*));
void		ft_toklstadd_back(t_tok_list **lst, t_tok_list *new);
t_tok_list	*lexer(char *line);
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
