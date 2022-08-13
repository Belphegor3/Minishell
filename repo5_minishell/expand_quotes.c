/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:18:40 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/05 10:45:08 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "expander.h"

void	expand_single_quote(t_vector *value, int *iter)
{
	ft_vecremove((value), *iter, *iter);
	while (((char *)value->buffer)[*iter] != '\'')
		(*iter)++;
	ft_vecremove((value), *iter, *iter);
}

void	expand_double_quote(t_vector *value, int *iter, char **envp)
{
	ft_vecremove((value), *iter, *iter);
	while (((char *)value->buffer)[*iter] != '\"')
	{
		if (((char *)value->buffer)[*iter] == '$')
			expand_variable(value, iter, envp);
		else
			(*iter)++;
	}
	ft_vecremove((value), *iter, *iter);
}

void	word_splitting(t_dlist **tokens, t_vector **word,
		int begin, int *iter)
{
	t_token		*new;
	t_dlist		*new_lst_elem;

	while (begin < *iter)
	{
		if (((char *)(ft_vecget(**word, begin)))[0] == ' ')
		{
			new = create_token(WORD);
			ft_vecinsert(new->value, 0, ft_vecget((**word), begin + 1),
				(*word)->length - begin - 1);
			ft_vecadd(new->value, "\0");
			ft_vecremove(*word, begin, (*word)->length - 1);
			ft_vecadd(*word, "\0");
			new_lst_elem = ft_dlstnew(new);
			new_lst_elem->next = (*tokens)->next;
			(*tokens)->next = new_lst_elem;
			(*tokens) = (*tokens)->next;
			(*iter) = (*iter) - begin;
			begin = 0;
			(*word) = new->value;
		}
			begin++;
	}
}

void	expander(t_dlist **tokens, t_vector *word, char **envp)
{
	int	i;
	int	index_before_expansion;

	i = 0;
	(void)tokens;
	while (word && (((char *)(ft_vecget(*word, 0)))[i]))
	{
		while ((((char *)(ft_vecget(*word, 0)))[i]) &&
			ft_strchr("'\"$", (((char *)(ft_vecget(*word, 0))))[i]) == NULL)
			i++;
		if ((((char *)(ft_vecget(*word, 0)))[i]) != '\0')
		{
			if ((((char *)(ft_vecget(*word, 0)))[i]) == '\'')
				expand_single_quote((word), &i);
			else if (((((char *)(ft_vecget(*word, 0)))[i])) == '\"')
				expand_double_quote((word), &i, envp);
			else
			{
				index_before_expansion = i;
				expand_variable(word, &i, envp);
				word_splitting(tokens, &word, index_before_expansion, &i);
			}
		}
	}
}
