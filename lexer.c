#include "minishell.h"
#include "lexer.h"

t_tok_list	*ft_toklstnew(t_token *token)
{
	return ((t_tok_list*)ft_lstnew((void*)token));
}

void	ft_toklstadd_back(t_tok_list **lst, t_tok_list *new)
{
	ft_lstadd_back((t_list**)lst, (t_list*)new);
}
void	ft_toklst_clear(t_tok_list **lst, void (*del)(void*))
{
	ft_lstclear((t_list**)lst, del);
}

static t_token	*take_word(char **iter)
{
	t_token		*token;
	char		special_characters[16];

	ft_strlcpy(special_characters, "|&;<>()$`\\\"' \t\n", 16);
	token = malloc(sizeof(t_token));
	assert(token != NULL);
	token->type = WORD;
	token->slice.start = *iter;
	token->slice.length = 1; 
	while ((*iter)[1] && ft_strchr(special_characters, (*iter)[1]) == NULL)
	{
		token->slice.length++;
		(*iter)++;
	}
	if (*iter)
		(*iter)++;
	return (token);
}

static t_token	*take_single_quote(char **iter)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	assert(token != NULL);
	token->type = QUOTE;
	(*iter)++;
	token->slice.start = *iter;
	token->slice.length = 1;
	while ((*iter)[1] != '\'')
	{
		token->slice.length++;
		(*iter)++;
	}
	(*iter) += 2;
	return (token);
}

static t_token	*take_double_quote(char **iter)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	assert(token != NULL);
	token->type = DQUOTE;
	(*iter)++;
	token->slice.start = *iter;
	token->slice.length = 1;
	while ((*iter)[1] != '\"')
	{
		token->slice.length++;
		(*iter)++;
	}
	(*iter) += 2;
	return (token);
}

t_tok_list	*lexer(char *line)
{
	t_tok_list	*token_list;
	char		*iter;

	iter = line;
	token_list = NULL;
	while (*iter)
	{
		if (*iter == '\'')
		{
			ft_toklstadd_back(&token_list, ft_toklstnew(take_single_quote(&iter)));
		}
		else if (*iter == '\"')
		{
			ft_toklstadd_back(&token_list, ft_toklstnew(take_double_quote(&iter)));
		}
		else if (*iter == '|')
		{
			t_token *token = malloc(sizeof(t_token));
			token->type = PIPE;
			token->slice.start = iter;
			token->slice.length = 1;
			ft_toklstadd_back(&token_list, ft_toklstnew(token));
			iter++;
		}
		else if (*iter == '>')
		{
			if (iter[1] == '>')
			{
				t_token *token = malloc(sizeof(t_token));
				token->type = GREATGREAT;
				token->slice.start = iter;
				token->slice.length = 2;
				ft_toklstadd_back(&token_list, ft_toklstnew(token));
				iter += 2;
			}
			else
			{
				t_token *token = malloc(sizeof(t_token));
				token->type = GREAT;
				token->slice.start = iter;
				token->slice.length = 1;
				ft_toklstadd_back(&token_list, ft_toklstnew(token));
				iter++;
			}
		}
		else if (*iter == '<')
		{
			t_token *token = malloc(sizeof(t_token));
			token->type = LESS;
			token->slice.start = iter;
			token->slice.length = 1;
			ft_toklstadd_back(&token_list, ft_toklstnew(token));
			iter++;
		}
		else if (*iter == ' ')
			iter++;
		else
		{
			ft_toklstadd_back(&token_list, ft_toklstnew(take_word(&iter)));
		}
	}
	return (token_list);
}
