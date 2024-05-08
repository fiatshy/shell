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
#include "libft/libft.h"

void	normal_split_nested(char const *s, char c, size_t *i, size_t *words)
{
	bool	quote;

	if (*(s + *i) == '"')
	{
		if (quote)
			quote = false;
		else
			quote = true;
	}
	if (*(s + *i) != c && !quote)
	{
		(*words)++;
		while (*(s + *i) != c && *(s + *i))
			(*i)++;
	}
	else
		(*i)++;
}

size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;
	bool	quote;

	i = 0;
	words = 0;
	quote = false;
	while (*(s + i))
		normal_split_nested(s, c, &i, &words);
	return (words);
}

size_t	count_length(char const *s, char c, size_t *i)
{
	size_t	j;

	j = 0;
	while (*(s + *i) != c && *(s + *i))
	{
		(*i)++;
		j++;
	}
	return (j);
}

typedef struct s_split
{
	size_t	i;
	size_t	j;
	size_t	idx;
	bool	quote;
}				t_split;

void	init_split(t_split *ts)
{
	ts->i = 0;
	ts->idx = 0;
	ts->quote = false;
}

void	split_arr_nested(char const *s, t_split ts, char *c)
{
	if (*(s + ts.i) == '"')
	{
		if (ts.quote)
			*c = ' ';
		else
			*c = '"';
	}
}

char	**split_arr(char **split, char const *s, char c)
{
	t_split	ts;

	init_split(&ts);
	while (*(s + ts.i))
	{
		split_arr_nested(s, ts, &c);
		if (*(s + ts.i) != c)
		{
			ts.j = count_length(s, c, &ts.i);
			split[ts.idx] = (char *) malloc (sizeof(char) * (ts.j + 1));
			if (split[ts.idx] == 0)
				return (0);
			ft_memcpy(split[ts.idx], s + ts.i - ts.j, ts.j);
			split[ts.idx][ts.j] = '\0';
			ts.idx++;
		}
		else
			ts.i++;
	}
	split[ts.idx] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char			**split;

	printf("%d\n", count_words(s, c));
	split = (char **) malloc (sizeof(char *) * (count_words(s, c) + 1));
	if (split == 0)
		return (0);
	split_arr(split, s, c);
	return (split);
}
