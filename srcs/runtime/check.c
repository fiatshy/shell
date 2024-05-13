/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:01:42 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:46:06 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_assert(bool condition, char *context)
{
	if (condition)
		return ;
	ft_putendl(context, STDERR_FILENO);
	exit(GENERAL);
}

bool	empty(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (!ft_isspace(input[i]))
			return (false);
	return (true);
}

bool	quotes(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '\"')
			cmd = ft_strchr(cmd + 1, '\"');
		if (cmd == NULL)
			return (false);
		if (*cmd == '\'')
			cmd = ft_strchr(cmd + 1, '\'');
		if (cmd == NULL)
			return (false);
		++cmd;
	}
	return (true);
}
