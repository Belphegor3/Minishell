/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:26:29 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/23 12:26:30 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"

t_syntax_node	*create_node(void)
{
	t_syntax_node	*node;

	node = malloc(sizeof(t_syntax_node));
	node->token = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	delete_syntax_tree(t_syntax_node *root)
{
	if (root)
	{
		destroy_token(root->token);
		if (root->left)
			delete_syntax_tree(root->left);
		if (root->right)
			delete_syntax_tree(root->right);
		free(root);
	}
}
