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

int	has_delimiters(const char *s, const char *d)
{
	while (*d)
	{
		if (*d == *s)
			return (1);
		d++;
	}
	return (0);
}

size_t	count_words_string(char const *s, char *c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (*(s + i))
	{
		if (!has_delimiters(s + i, c))
		{
			words++;
			while (!has_delimiters(s + i, c) && *(s + i))
				i++;
		}
		else
			i++;
	}
	return (words);
}

size_t	count_length_string(char const *s, char *c, size_t *i)
{
	size_t	j;

	j = 0;
	while (!has_delimiters(s + *i, c) && *(s + *i))
	{
		(*i)++;
		j++;
	}
	return (j);
}

char	*split_routine(size_t *i, char const *s, size_t *j, char *operand)
{
	size_t	k;
	size_t	l;
	size_t	cmp_index;

	k = 1;
	l = 0;
	cmp_index = 0;
	k = *i;
	k--;
	while (*(s + k) == ' ')
		k--;
	cmp_index = k;
	if (k - 1 >= 0)
		cmp_index = k - 1;
	ft_memset(operand, ' ', 3);
	if (ft_strncmp(s + cmp_index, "<<", 2) == 0)
		ft_memcpy(operand, "<< ", 3);
	else if (ft_strncmp(s + cmp_index, ">>", 2) == 0)
		ft_memcpy(operand, ">> ", 3);
	else if (ft_strncmp(s + k, ">", 1) == 0)
		ft_memcpy(operand, "> ", 3);
	else if (ft_strncmp(s + k, "<", 1) == 0)
		ft_memcpy(operand, "< ", 3);
	*j = count_length_string(s, "<>", i);
	return (operand);
}

typedef struct s_str
{
	size_t	i;
	size_t	j;
	size_t	idx;
	char	*operand;
}			t_str;

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

// int	main(void)
// {
// 	char	*s = "ls < abc << b > c";
// 	char	**split;

// 	split = ft_split_string(s, "<>");
// 	int	i = 0;
// 	while (split[i])
// 	{
// 		printf("%s\n", split[i]);
// 		i++;
// 	}
// 	return (0);
// }