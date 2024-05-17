/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_nested.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:22:55 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:22:57 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

void	count_quote_nest_in_nest(size_t *words, char const *s, \
	size_t *i, char c)
{
	(*words)++;
	while (*(s + (*i)) != c && *(s + (*i)))
	{
		if (*(s + (*i)) == '"')
			c = '"';
		else if (*(s + (*i)) == '\'')
			c = '\'';
		(*i)++;
	}
}

void	count_quote_nested(char c, char const *s, size_t *i, size_t *words)
{
	char	save;

	save = 0;
	if (c == '"')
	{
		c = save;
		(*i)++;
		(*words)--;
	}
	else if (c == '\'')
	{
		c = save;
		(*i)++;
		(*words)--;
	}
	if (*(s + (*i)) != c)
		count_quote_nest_in_nest(words, s, i, c);
	else
		(*i)++;
}

size_t	count_words_quote(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (*(s + i))
		count_quote_nested(c, s, &i, &words);
	return (words);
}

void	count_length_quote_nested(char const *s, size_t *i, char *c, size_t *j)
{
	while (*(s + *i) != *c && *(s + *i))
	{
		if (*(s + *i) == '"')
			*c = '"';
		else if (*(s + *i) == '\'')
			*c = '\'';
		(*i)++;
		(*j)++;
	}
}
