/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 05:01:27 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:45:56 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"
#include "libft.h"

static inline void	padding(char c, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		ft_putchar(c, STDOUT_FILENO);
		ft_putchar(c, STDOUT_FILENO);
	}
}

void	rb_node(t_node *node, int level)
{
	if (node == NULL)
	{
		padding('\t', level);
		ft_putendl("NIL", STDOUT_FILENO);
	}
	else
	{
		rb_node(node->right, level + 1);
		padding('\t', level);
		if (get_color(node) == BLACK)
		{
			ft_putstr("(", STDOUT_FILENO);
			ft_putstr((char *)(node->key), STDOUT_FILENO);
			ft_putstr(") : ", STDOUT_FILENO);
			ft_putendl((char *)(node->value), STDOUT_FILENO);
		}
		else
		{
			ft_putstr((char *)(node->key), STDOUT_FILENO);
			ft_putstr(" : ", STDOUT_FILENO);
			ft_putendl((char *)(node->value), STDOUT_FILENO);
		}
		rb_node(node->left, level + 1);
	}
}

void	rb_print(t_rb *tree)
{
	rb_node(tree->root, 0);
	ft_putendl("-------------------------------------------", STDOUT_FILENO);
}

void	rb_order(t_node *node)
{
	if (node == NULL)
		return ;
	rb_order(node->left);
	rb_order(node->right);
	if (!ft_strncmp((char *)(node->key), "#", BUFFER_SIZE)
		|| !ft_strncmp((char *)(node->key), "*", BUFFER_SIZE)
		|| !ft_strncmp((char *)(node->key), "?", BUFFER_SIZE))
		return ;
	if (!*((char *)(node->value)))
		return ;
	ft_putstr((char *)(node->key), STDOUT_FILENO);
	ft_putstr("=", STDOUT_FILENO);
	ft_putendl((char *)(node->value), STDOUT_FILENO);
}
