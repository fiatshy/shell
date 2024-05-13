/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:01:15 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:03:05 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"
#include "libft.h"

void	rb_delete(t_rb *tree, void *key)
{
	t_node	*node;
	t_node	*next;
	t_node	*child;

	node = get_node(tree, key, NULL);
	if (node == NULL)
		return ;
	if (node->left != NULL && node->right != NULL)
	{
		ft_free((void **)(&(node->key)));
		ft_free((void **)(&(node->value)));
		next = get_min(node->right);
		node->key = next->key;
		node->value = next->value;
		node = next;
	}
	rb_assert(node->left == NULL || node->right == NULL, \
		RASSERT "(node->left == NULL || node->right == NULL), " RB_DELETE \
		RDELETE_1_FILE "line 42.");
	if (node->right == NULL)
		child = node->left;
	else
		child = node->right;
	delete_internal(tree, node, child);
}
