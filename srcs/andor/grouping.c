/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:30 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:32 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_open_value(t_cmd_struct *tcst, char *s, int i)
{
	while (*s)
	{
		if (*s == '(')
		{
			tcst->open_index = i;
			tcst->close_index = i;
			tcst->tcmd[tcst->open_index]->parenthesis[0] = i;
		}
		s++;
	}
}

void	set_close_value(t_cmd_struct *tcst, char *s, int i)
{
	while (*s)
	{
		if (*s == ')')
		{
			tcst->tcmd[tcst->close_index]->parenthesis[1] = i;
			tcst->close_index--;
		}
		s++;
	}
}

int	check_grouping_or(t_cmd_struct *tcst, int *i, int *proceed)
{
	if (tcst->status == 0)
	{
		*proceed = false;
		if (tcst->tcmd[*i]->parenthesis[0] != -1)
		{
			*i = tcst->tcmd[*i]->parenthesis[1] + 1;
			return (-1);
		}
	}
	else if (tcst->status != 0)
		*proceed = true;
	return (0);
}

int	check_grouping_and(t_cmd_struct *tcst, int *i, int *proceed)
{
	if (tcst->status == 0)
		*proceed = true;
	else if (tcst->status != 0)
	{
		*proceed = false;
		if (tcst->tcmd[*i]->parenthesis[0] != -1)
		{
			*i = tcst->tcmd[*i]->parenthesis[1] + 1;
			return (-1);
		}
	}
	return (0);
}

int	check_grouping(t_cmd_struct *tcst, int *i, int *proceed)
{
	int	res;

	if (*i != 0)
	{
		if (ft_strncmp(tcst->tcmd[*i - 1]->next_delimiter, "||", 2) == 0)
		{
			res = check_grouping_or(tcst, i, proceed);
			if (res == -1)
				return (-1);
		}
		else if (ft_strncmp(tcst->tcmd[*i - 1]->next_delimiter, "&&", 2) == 0)
		{
			res = check_grouping_and(tcst, i, proceed);
			if (res == -1)
				return (-1);
		}
	}
	return (0);
}
