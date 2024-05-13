/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:01:24 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:25:32 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

static inline void	case_2(t_rb *tree, t_node **node, t_node **parent,
		t_node **grandparent)
{
	t_node	*uncle;

	uncle = (*grandparent)->left;
	if (uncle && get_color(uncle) == RED)
	{
		set_color(*grandparent, RED);
		set_color(*parent, BLACK);
		set_color(uncle, BLACK);
		*node = *grandparent;
	}
	else
	{
		if (*node == (*parent)->left)
		{
			right_rotate(tree, *parent);
			*node = *parent;
			*parent = get_parent(*parent);
		}
		set_color(*parent, BLACK);
		set_color(*grandparent, RED);
		left_rotate(tree, *grandparent);
	}
}

static inline void	case_1(t_rb *tree, t_node **node, t_node **parent,
		t_node **grandparent)
{
	t_node	*uncle;

	uncle = (*grandparent)->right;
	if (uncle && get_color(uncle) == RED)
	{
		set_color(*grandparent, RED);
		set_color(*parent, BLACK);
		set_color(uncle, BLACK);
		*node = *grandparent;
	}
	else
	{
		if (*node == (*parent)->right)
		{
			left_rotate(tree, *parent);
			*node = *parent;
			*parent = get_parent(*parent);
		}
		set_color(*parent, BLACK);
		set_color(*grandparent, RED);
		right_rotate(tree, *grandparent);
	}
}

void	insert_internal(t_rb *tree, t_node *node, t_node *parent)
{
	t_node	*grandparent;

	while (parent != NULL && get_color(parent) == RED)
	{
		grandparent = get_parent(parent);
		if (parent == grandparent->left)
			case_1(tree, &node, &parent, &grandparent);
		else
			case_2(tree, &node, &parent, &grandparent);
		parent = get_parent(node);
	}
	set_color(tree->root, BLACK);
}
