/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first_nested.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:22:42 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:22:44 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"
#include "libft/libft.h"

void	count_words_first_nested(const char *s, int i, bool *quote)
{
	if (*(s + i) == '"' || *(s + i) == '\'')
	{
		if (*quote)
			*quote = false;
		else
			*quote = true;
	}
}

size_t	count_words_first(char const *s, char c)
{
	size_t	i;
	size_t	words;
	bool	quote;

	i = 0;
	words = 0;
	quote = false;
	while (*(s + i))
	{
		count_words_first_nested(s, i, &quote);
		if (*(s + i) != c && !quote)
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

int	has_delimiter_first(char s)
{
	char	*delim;

	delim = "|&";
	while (*delim)
	{
		if (*delim == s)
			return (1);
		delim++;
	}
	return (0);
}
