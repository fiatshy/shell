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

	i = 0;
	idx = 0;
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
