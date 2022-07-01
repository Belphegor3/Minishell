/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tok_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:38:27 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/15 01:38:34 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_tok_list	*ft_toklstnew(t_token *token)
{
	return ((t_tok_list *)ft_lstnew((void *)token));
}

void	ft_toklstadd_back(t_tok_list **lst, t_tok_list *new)
{
	ft_lstadd_back((t_list **)lst, (t_list *)new);
}

void	ft_toklst_clear(t_tok_list **lst, void (*del)(void*))
{
	ft_lstclear((t_list **)lst, del);
}

t_tok_list	*ft_toklstlast(t_tok_list *lst)
{
	return ((t_tok_list *)ft_lstlast((t_list *)lst));
}
