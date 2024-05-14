/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:21:26 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/07 09:21:28 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

int	get_closed_index(t_cmd_struct *tcst, int index)
{
	while (index < tcst->n)
	{
		if (tcst->tcmd[index]->close)
			return (index); /* sync with i++ in prepare_execute*/
		index++;
	}
	return (0);
}

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

void	copy_string(t_cmd **tcmd, char *src, int len)
{
	(*tcmd)->cmd = malloc (len + 1);
	ft_memcpy((*tcmd)->cmd, src, len);
	(*tcmd)->cmd[len] = 0;
}

void	copy_string_char(char **s, char *src, int len)
{
	int		i;
	char	delim;
	(*s) = malloc (len +1);
	ft_memcpy((*s), src, len);
	(*s)[len] = 0;
	i = 0;
	if ((*s)[0] == '\'' | (*s)[0] == '\"')
	{
		delim = (*s)[0];
		if ((*s)[len - 1] == delim)
			*s = ft_strtrim(*s, &delim);
	}

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
			//if (tcst->tcmd[i]->next_delimiter[0] == '|')
			//	cnt++;
		}
		i++;
	}
	return (cnt);
}

void	check_redirection(char **s, bool *quote, int *count)
{
	if ((**s == '"' || **s == '\'') && !(*quote))
		*quote = true;
	else if ((**s == '"' || **s == '\'') && *quote)
		*quote = false;
	if (!(*quote))
	{
		if (ft_strncmp(*s, ">>", 2) == 0)
		{
			(*s)++;
			(*count)++;
		}
		else if (ft_strncmp(*s, "<<", 2) == 0)
		{
			(*s)++;
			(*count)++;
		}
		else if (ft_strncmp(*s, ">", 1) == 0)
			(*count)++;
		else if (ft_strncmp(*s, "<", 1) == 0)
			(*count)++;
	}
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
