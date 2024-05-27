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

#include "libft.h"

size_t	count_words_dollar(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			words++;
			while (*(s + i) != c && *(s + i))
				i++;
		}
		else
			i++;
	}
	return (words);
}

size_t	count_length_dollar(char const *s, char *c, size_t *i)
{
	size_t	j;

	j = 0;
	while (*(s + *i) != *c && *(s + *i))
	{
		(*i)++;
		j++;
	}
	*c = '\t';
	return (j);
}

static void	dollar_nested(int *idx, size_t *i, int *flag)
{
	(*idx)++;
	if (*flag)
	{
		*flag = 0;
		(*i)++;
	}
}

char	**split_arr_dollar(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		idx;
	int		flag;

	i = 0;
	idx = 0;
	flag = 1;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			j = count_length_dollar(s, &c, &i);
			split[idx] = (char *) malloc (j + 1);
			if (split[idx] == 0)
				return (0);
			ft_memcpy(split[idx], s + i - j, j);
			split[idx][j] = '\0';
			dollar_nested(&idx, &i, &flag);
		}
		else
			i++;
	}
	split[idx] = 0;
	return (split);
}

char	**ft_split_dollar(char const *s, char c)
{
	char			**split;

	split = (char **) malloc (sizeof(char *) * (2 + 1));
	if (split == 0)
		return (0);
	split_arr_dollar(split, s, c);
	return (split);
}
