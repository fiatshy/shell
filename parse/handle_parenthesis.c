/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:02:21 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 18:02:24 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

int	has_parenthesis(char *s)
{
	if (*s == '(')
		return (1);
	else if (*s == ')')
		return (2);
	return (0);
}

char	*get_first_delimiter(char *s)
{
	bool	quote;

	quote = false;
	while (*s)
	{
		if ((*s == '"' || *s == '\'') && !quote)
			quote = true;
		else if ((*s == '"' || *s == '\'') && quote)
			quote = false;
		if (!quote)
		{
			if (ft_strncmp("||", s, 2) == 0)
				return ("||");
			else if (*s == '|')
				return ("|");
			else if (ft_strncmp("&&", s, 2) == 0)
				return ("&&");
		}
		s++;
	}
	return (NULL);
}

int	has_delimiter(char *s)
{
	if (ft_strncmp("||", s, 2) == 0)
		return (2);
	else if (*s == '|')
		return (1);
	else if (ft_strncmp("&&", s, 2) == 0)
		return (2);
	return (0);
}

int	has_open_parenthesis(char *s)
{
	bool	quote;

	quote = false;
	while (*s)
	{
		if ((*s == '"' || *s == '\'') && !quote)
			quote = true;
		else if ((*s == '"' || *s == '\'') && quote)
			quote = false;
		if (!quote)
		{
			if (*s == '(')
				return (1);
		}
		s++;
	}
	return (0);
}

int	has_close_parenthesis(char *s)
{
	bool	quote;

	quote = false;
	while (*s)
	{
		if ((*s == '"' || *s == '\'') && !quote)
			quote = true;
		else if ((*s == '"' || *s == '\'') && quote)
			quote = false;
		if (!quote)
		{
			if (*s == ')')
				return (1);
		}
		s++;
	}
	return (0);
}
