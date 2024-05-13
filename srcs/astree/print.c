/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 04:57:49 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:43:45 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

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

void	as_syntax(t_as *syntax, int level)
{
	if (syntax == NULL)
	{
		padding('\t', level);
		ft_putendl("NIL", STDOUT_FILENO);
	}
	else
	{
		as_syntax(syntax->right, level + 1);
		padding('\t', level);
		ft_putendl(syntax->token, STDOUT_FILENO);
		as_syntax(syntax->left, level + 1);
	}
}

void	as_print(t_as *syntax)
{
	as_syntax(syntax, 0);
	ft_putendl("-------------------------------------------", STDOUT_FILENO);
}
