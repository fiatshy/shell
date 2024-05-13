/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:01:32 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:01:12 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_color	get_color(t_node *node)
{
	if (node == NULL)
		return (BLACK);
	return (node->color);
}

void	set_color(t_node *node, t_color color)
{
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " SET_COLOR RUTIL_1_FILE "line 39.");
	node->color = color;
}

t_node	*get_parent(t_node *node)
{
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " GET_PARENT RUTIL_1_FILE "line 53.");
	return (node->parent);
}

void	set_parent(t_node *node, t_node *parent)
{
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " SET_PARENT RUTIL_1_FILE "line 68.");
	node->parent = parent;
}

t_node	*get_sibling(t_node *node)
{
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " GET_SIBLING RUTIL_1_FILE "line 82.");
	rb_assert(node->parent != NULL, \
		RASSERT "(node->parent != NULL), " GET_SIBLING RUTIL_1_FILE "line 84.");
	if (node == get_parent(node)->left)
		return (get_parent(node)->right);
	return (get_parent(node)->left);
}
