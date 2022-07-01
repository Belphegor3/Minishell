/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:01:58 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/23 00:02:01 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "libft.h"
# include "minishell.h"

int		expand_variable(t_vector *word, int *iter, char **envp);
void	expander(t_tok_list **tokens, t_vector *word, char **envp);
#endif
