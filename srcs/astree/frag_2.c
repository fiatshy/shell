/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frag_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:57:46 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:45:09 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

static inline t_as	*insert_lt(t_as *root, t_as *frag)
{
	frag->right = root;
	return (frag);
}

static inline t_as	*insert_eq(t_as *root, t_as *frag)
{
	if (frag->type == SCLN || frag->type == PIPE || (frag->heredoc
			&& !root->heredoc))
	{
		frag->right = root;
		return (frag);
	}
	root->right = as_insert(root->right, frag);
	return (root);
}

static inline t_as	*insert_gt(t_as *root, t_as *frag)
{
	if (root->type == PIPE)
	{
		if (root->right != NULL)
			root->left = as_insert(root->left, frag);
		else
			root->right = as_insert(root->right, frag);
	}
	else if (root->type == RDR)
	{
		if (root->left == NULL)
			root->left = as_insert(root->left, frag);
		else
			root->right = as_insert(root->right, frag);
	}
	return (root);
}

t_as	*as_insert(t_as *syntax, t_as *frag)
{
	t_as	*root;

	if (syntax == NULL)
		return (frag);
	root = syntax;
	if (frag->type < root->type)
		root = insert_lt(root, frag);
	else if (frag->type == root->type)
		root = insert_eq(root, frag);
	else
		root = insert_gt(root, frag);
	return (root);
}

void	as_free(t_as *syntax)
{
	if (syntax->right != NULL)
		as_free(syntax->right);
	if (syntax->left != NULL)
		as_free(syntax->left);
	ft_free((void **)(&syntax));
}
