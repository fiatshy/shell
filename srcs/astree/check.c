/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 04:57:36 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:43:25 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

void	as_assert(bool condition, char *context)
{
	if (condition)
		return ;
	ft_putendl(context, STDERR_FILENO);
	exit(GENERAL);
}

static inline bool	as_mixin(t_as *syntax)
{
	t_as	*lchild;
	t_as	*rchild;

	lchild = syntax->left;
	rchild = syntax->right;
	if (!syntax->root && syntax->type == PIPE)
		if (lchild != NULL && lchild->type == RDR)
			return (true);
	if (syntax->type == PIPE)
	{
		if (lchild != NULL && lchild->heredoc)
			return (true);
		if (rchild != NULL && rchild->heredoc)
			return (true);
	}
	return (false);
}

bool	as_check(t_as *syntax)
{
	if (syntax == NULL)
		return (true);
	if (syntax->type == PIPE || syntax->type == RDR)
		if (syntax->left == NULL)
			return (false);
	if (as_mixin(syntax))
		return (false);
	if (!as_check(syntax->right) || !as_check(syntax->left))
		return (false);
	return (true);
}
