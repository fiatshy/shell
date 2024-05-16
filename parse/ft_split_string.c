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

void	init_string(t_str *ts)
{
	ts->i = 0;
	ts->idx = 0;
	ts->operand = malloc (sizeof(char) * 4);
}

char	**split_arr_string(char **split, char const *s, char *c)
{
	t_str	ts;

	init_string(&ts);
	while (*(s + ts.i))
	{
		if (!has_delimiters(s + ts.i, c))
		{
			split_routine(&ts.i, s, &ts.j, ts.operand);
			split[ts.idx] = (char *) malloc (sizeof(char) * (ts.j + 3 + 1));
			if (split[ts.idx] == 0)
				return (0);
			ft_memcpy(split[ts.idx], ts.operand, 3);
			ft_memcpy(&split[ts.idx][2], s + ts.i - ts.j, ts.j);
			split[ts.idx][ts.j + 2] = '\0';
			ts.idx++;
		}
		else
			ts.i++;
	}
	free(ts.operand);
	split[ts.idx] = 0;
	return (split);
}

char	**ft_split_string(char const *s, char *d)
{
	char			**split;

	split = (char **) malloc (sizeof(char *) * (count_words_string(s, d) + 1));
	if (split == 0)
		return (0);
	split_arr_string(split, s, d);
	return (split);
}
