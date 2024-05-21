/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_string_nested.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:23:12 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/21 09:57:05 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	size_t	cmp_index;

	k = 1;
	cmp_index = 0;
	k = *i;
	k--;
	while (*(s + k) == ' ')
		k--;
	cmp_index = k;
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
