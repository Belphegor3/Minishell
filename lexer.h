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

typedef struct	s_slice
{
	char	*start;
	size_t	length;
}t_slice;

typedef struct	s_token
{
	enum e_token_type	type;
	t_slice				slice;
}t_token;

typedef struct	s_tok_list
{
	t_token	*token;
	struct s_tok_list	*next;
}t_tok_list;

t_tok_list	*ft_toklstnew(t_token *token);
void		ft_toklst_clear(t_tok_list **lst, void (*del)(void*));
void		ft_toklstadd_back(t_tok_list **lst, t_tok_list *new);
t_tok_list	*lexer(char *line);
#endif
