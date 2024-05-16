/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_dollar_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:11 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:14 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

int	has_double_quote(char *split_arg)
{
	while (*split_arg)
	{
		if (*split_arg == '"')
			return (1);
		split_arg++;
	}
	return (0);
}

int	is_double_is_outer(char *split_arg)
{
	while (*split_arg)
	{
		if (*split_arg == '\'')
			return (0);
		else if (*split_arg == '\"')
			return (1);
		split_arg++;
	}
	return (0);
}

int	has_dollar(char *split_arg)
{
	int	i;

	i = 0;
	while (*(split_arg + i))
	{
		if (*(split_arg + i) == '$')
			return (i);
		i++;
	}
	return (0);
}

int	space_after_dollar(char *string)
{
	int	i;

	i = 0;
	while (*(string + i))
	{
		if (*(string + i) == ' ')
			return (i);
		i++;
	}
	return (0);
}
