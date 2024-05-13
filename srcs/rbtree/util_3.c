/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:01:39 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:12:48 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_node	*prev_element(t_node *node)
{
	t_node	*parent;

	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " PREV_ELEMENT RUTIL_3_FILE "line 27.");
	if (node->left != NULL)
		return (get_max(node->left));
	parent = get_parent(node);
	while (parent != NULL && parent->left == node)
	{
		node = parent;
		parent = get_parent(node);
	}
	return (parent);
}

t_node	*next_element(t_node *node)
{
	t_node	*parent;

	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " NEXT_ELEMENT RUTIL_3_FILE "line 52.");
	if (node->right != NULL)
		return (get_min(node->right));
	parent = get_parent(node);
	while (parent != NULL && parent->right == node)
	{
		node = parent;
		parent = get_parent(node);
	}
	return (parent);
}

void	left_rotate(t_rb *tree, t_node *node)
{
	t_node	*x;
	t_node	*y;
	t_node	*parent;

	x = node;
	y = node->right;
	parent = get_parent(node);
	if (parent == NULL)
		tree->root = y;
	else
	{
		if (parent->left == x)
			parent->left = y;
		else
			parent->right = y;
	}
	set_parent(y, parent);
	set_parent(x, y);
	x->right = y->left;
	if (y->left != NULL)
		set_parent(y->left, x);
	y->left = x;
}

void	right_rotate(t_rb *tree, t_node *node)
{
	t_node	*x;
	t_node	*y;
	t_node	*parent;

	x = node;
	y = node->left;
	parent = get_parent(node);
	if (parent == NULL)
		tree->root = y;
	else
	{
		if (parent->left == x)
			parent->left = y;
		else
			parent->right = y;
	}
	set_parent(y, parent);
	set_parent(x, y);
	x->left = y->right;
	if (y->right != NULL)
		set_parent(y->right, x);
	y->right = x;
}

void	transplant(t_rb *tree, t_node *u, t_node *v)
{
	if (get_parent(u) == NULL)
		tree->root = v;
	else
	{
		if (u == get_parent(u)->left)
			get_parent(u)->left = v;
		else
			get_parent(u)->right = v;
	}
	if (v != NULL)
		v->parent = get_parent(u);
}
