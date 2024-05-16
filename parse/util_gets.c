/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_gets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:02:12 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 18:02:13 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

int	get_closed_index(t_cmd_struct *tcst, int index)
{
	while (index < tcst->n)
	{
		if (tcst->tcmd[index]->close)
			return (index);
		index++;
	}
	return (0);
}

int	get_no_of_command(char *s)
{
	bool	quote;
	char	c;
	int		count;

	quote = false;
	count = 0;
	while (*s)
	{
		if ((*s == '"' || *s == '\'') && !quote)
			quote = true;
		else if ((*s == '"' || *s == '\'') && quote)
			quote = false;
		if (!quote && has_delimiter(s))
		{
			if (has_delimiter(s) == 2)
				s++;
			count++;
		}
		s++;
	}
	return (count + 1);
}

int	get_no_of_pipes(t_cmd_struct *tcst)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (i < tcst->n)
	{
		if (tcst->tcmd[i]->next_delimiter != NULL)
		{
			if (ft_strncmp(tcst->tcmd[i]->next_delimiter, "|", 2) == 0)
				cnt++;
		}
		i++;
	}
	return (cnt);
}

int	get_no_of_redirection(t_cmd *t)
{
	char	*s;
	int		count;
	bool	quote;

	count = 0;
	s = t->cmd;
	quote = false;
	while (*s)
	{
		check_redirection(&s, &quote, &count);
		s++;
	}
	return (count);
}

int	get_length_of_args(char **split_arg)
{
	int	i;

	i = 0;
	while (split_arg[i])
		i++;
	return (i);
}
