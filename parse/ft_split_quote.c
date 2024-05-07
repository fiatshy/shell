/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:14:20 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 17:20:07 by sunghyki         ###   ########.fr       */
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
	bool	quote;
	char	save;

	i = 0;
	words = 0;
	quote = false;
	save = c;
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

size_t	count_length_quote(char const *s, char c, size_t *i)
{
	size_t	j;
	char	save;

	j = 0;
	save = c;
	count_length_quote_nested(s, i, &c, &j);
	if (c == '"' || c == '\'')
	{
		c = save;
		(*i)++;
		j++;
		while (*(s + *i) != c && *(s + *i))
		{
			(*i)++;
			j++;
		}
	}
	return (j);
}

char	**split_arr_quote(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	idx;
	bool	quote;

	i = 0;
	idx = 0;
	quote = false;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			j = count_length_quote(s, c, &i);
			split[idx] = (char *) malloc (sizeof(char) * (j + 1));
			if (split[idx] == 0)
				return (0);
			ft_memcpy(split[idx], s + i - j, j);
			split[idx][j] = '\0';
			idx++;
		}
		else
			i++;
	}
	split[idx] = 0;
	return (split);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**split;

	split = (char **) malloc (sizeof(char *) * (count_words_quote(s, c) + 1));
	if (split == 0)
		return (0);
	split_arr_quote(split, s, c);
	return (split);
}

// int	main(void)
// {
// 	char *s = "echo \'$USER | grep nam\' | grep test";
// 	char **split = ft_split_quote(s, '|');
// 	printf("=%s =%s =%s\n", split[0], split[1], split[2]);
// 	char	**split2 = ft_split_quote(split[0], ' ');
// 	printf("%s =%s\n", split2[0], split2[1]);
// }
