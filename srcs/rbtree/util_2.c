/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:01:35 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:12:38 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

void	set_child(t_rb *tree, t_node *node, t_node *child)
{
	int	res;

	rb_assert(tree != NULL, \
		RASSERT "(tree != NULL), " SET_CHILD RUTIL_2_FILE "line 29.");
	res = tree->compare(node->key, child->key);
	rb_assert(res, \
		RASSERT "(res), " SET_CHILD RUTIL_2_FILE "line 32.");
	if (res > 0)
		node->left = child;
	else
		node->right = child;
}

t_node	*get_min(t_node *node)
{
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " GET_MIN RUTIL_2_FILE "line 47.");
	while (node->left != NULL)
		node = node->left;
	return (node);
}

t_node	*get_max(t_node *node)
{
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " GET_MAX RUTIL_2_FILE "line 63.");
	while (node->right != NULL)
		node = node->right;
	return (node);
}

t_node	*min_element(t_rb *tree)
{
	rb_assert(tree != NULL, \
		RASSERT "(tree != NULL), " MIN_ELEMENT RUTIL_2_FILE "line 81.");
	if (tree->root == NULL)
		return (NULL);
	return (get_min(tree->root));
}

t_node	*max_element(t_rb *tree)
{
	rb_assert(tree != NULL, \
		RASSERT "(tree != NULL), " MAX_ELEMENT RUTIL_2_FILE "line 97.");
	if (tree->root == NULL)
		return (NULL);
	return (get_max(tree->root));
}
