/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:01:11 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:45:50 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"
#include "libft.h"

void	rb_assert(bool condition, char *context)
{
	if (condition)
		return ;
	ft_putendl(context, STDERR_FILENO);
	exit(GENERAL);
}

bool	is_root(t_node *node)
{
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " IS_ROOT RCHECK_FILE "line 40.");
	return (get_parent(node) == NULL);
}

bool	is_black(t_node *node)
{
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " IS_BLACK RCHECK_FILE "line 54.");
	return (get_color(node) == BLACK);
}

bool	is_red(t_node *node)
{
	rb_assert(node != NULL, \
		RASSERT "(node != NULL), " IS_RED RCHECK_FILE "line 69.");
	return (get_color(node) == RED);
}

int	rb_compare(void *key_a, void *key_b)
{
	return (ft_strncmp((char *)key_a, (char *)key_b, BUFFER_SIZE));
}
