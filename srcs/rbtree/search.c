/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:01:30 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:46:00 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_node	*get_node(t_rb *tree, void *key, t_node **parent)
{
	int		res;
	t_node	*current;

	rb_assert(tree != NULL, \
		RASSERT "(tree != NULL), " GET_NODE RSEARCH_FILE "line 31.");
	current = tree->root;
	while (current != NULL)
	{
		res = tree->compare(current->key, key);
		if (!res)
			return (current);
		else
		{
			if (parent != NULL)
				*parent = current;
			if (res > 0)
				current = current->left;
			else
				current = current->right;
		}
	}
	return (NULL);
}

void	*get_value(t_rb *tree, void *key)
{
	t_node	*node;

	rb_assert(tree != NULL, \
		RASSERT "(tree != NULL), " GET_VALUE RSEARCH_FILE "line 66.");
	node = get_node(tree, key, NULL);
	if (node == NULL)
		return (NULL);
	return (node->value);
}
