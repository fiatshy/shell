/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:01:21 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:00:26 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_rb	*rb_init(t_rb_cmp_fn compare)
{
	t_rb	*tree;

	ft_calloc((void **)(&tree), 1, sizeof(t_rb));
	rb_assert(tree != NULL, \
		RASSERT "(tree != NULL), " RB_INIT RINSERT_1_FILE "line 28.");
	tree->root = NULL;
	rb_assert(compare != NULL, \
		RASSERT "(compare != NULL), " RB_INIT RINSERT_1_FILE "line 31.");
	tree->compare = compare;
	return (tree);
}

t_node	*make_node(void *key, void *value)
{
	t_node	*node;

	ft_calloc((void **)(&node), 1, sizeof(t_node));
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " MAKE_NODE RINSERT_1_FILE "line 51.");
	node->key = key;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

void	rb_insert(t_rb *tree, void *key, void *value)
{
	t_node	*parent;
	t_node	*node;
	t_node	*prev;

	parent = NULL;
	rb_assert(key != NULL && value != NULL, RASSERT \
		"(key != NULL && value != NULL), " RB_INSERT RINSERT_1_FILE "line 80.");
	prev = get_node(tree, key, &parent);
	if (prev != NULL)
	{
		ft_free((void **)(&key));
		ft_free((void **)(&(prev->value)));
		prev->value = value;
	}
	else
	{
		node = make_node(key, value);
		set_color(node, RED);
		set_parent(node, parent);
		if (parent == NULL)
			tree->root = node;
		else
			set_child(tree, parent, node);
		insert_internal(tree, node, parent);
	}
}
