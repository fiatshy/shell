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

int	count_length_first_nested(char const *s, size_t *i, size_t *j, bool *first)
{
	bool	delim;
	bool	quote;

	delim = false;
	quote = false;
	while (!delim && *(s + *i))
	{
		if ((*(s + *i) == '"' || *(s + *i) == '\'') && !quote)
			quote = true;
		else if ((*(s + *i) == '"' || *(s + *i) == '\'') && quote)
			quote = false;
		if (!quote)
		{
			delim = has_delimiter_first(*(s + *i));
			if (delim != 0)
			{
				*first = false;
				break ;
			}
		}
		(*i)++;
		(*j)++;
	}
	*first = false;
	return (0);
}

size_t	count_length_first(char const *s, size_t *i, bool *first)
{
	size_t	j;

	j = 0;
	if (*first)
		count_length_first_nested(s, i, &j, first);
	else if (!*first)
	{
		while (*(s + *i))
		{
			(*i)++;
			j++;
		}
	}
	return (j);
}

void	init_first(t_first *tf)
{
	tf->i = 0;
	tf->idx = 0;
	tf->quote = false;
	tf->first = true;
}

char	**split_arr_first(char **split, char const *s)
{
	t_first	tf;

	init_first(&tf);
	while (*(s + tf.i))
	{
		if (*(s + tf.i) == '"' || *(s + tf.i) == '\'')
			tf.quote = true;
		else if (*(s + tf.i) == '"' || *(s + tf.i) == '\'')
			tf.quote = false;
		if (!has_delimiter_first(*(s + tf.i)) && !tf.quote)
		{
			tf.j = count_length_first(s, &tf.i, &tf.first);
			split[tf.idx] = (char *) malloc (sizeof(char) * (tf.j + 1));
			if (split[tf.idx] == 0)
				return (0);
			ft_memcpy(split[tf.idx], s + tf.i - tf.j, tf.j);
			split[tf.idx][tf.j] = '\0';
			tf.idx++;
		}
		else
			tf.i++;
	}
	split[tf.idx] = 0;
	return (split);
}

char	**ft_split_first(char const *s)
{
	char			**split;

	split = (char **) malloc (sizeof(char *) * (2 + 1));
	if (split == 0)
		return (0);
	split_arr_first(split, s);
	return (split);
}
