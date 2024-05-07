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

#include "newshell.h"
#include "libft/libft.h"

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
		if (*(s + i) == '"')
		{
			if (quote)
				quote = false;
			else
				quote = true;
		}

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

int		has_delimiter_first(char s)
{
	char	*delim = "|&";

	while (*delim)
	{
		if (*delim == s)
			return (1);
		delim++;
	}
	return (0);
}

size_t	count_length_first(char const *s, char c, size_t *i, bool *first)
{
	size_t	j;
	bool	quote;
	bool	delim;

	j = 0;
	quote = false;
	delim = false;
	if (*first)
	{
		//while (*(s + *i) != c && *(s + *i))
		// while (!has_delimiter_first(*(s + *i)) && *(s + *i))
		// {
		// 	(*i)++;
		// 	j++;
		// }
		while (!delim && *(s + *i))
		{
			if (*(s + *i) == '"' && !quote)
				quote = true;
			else if (*(s + *i) == '"' && quote)
				quote = false;
			if (!quote)
			{
				delim = has_delimiter_first(*(s + *i));
				if (delim != 0)
				{
					*first = false;
					break;
				}
			}
			(*i)++;
			j++;
		}
		*first = false;
	}
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

char	**split_arr_first(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	idx;
	bool	quote;
	bool	first;

	i = 0;
	idx = 0;
	quote = false;
	first = true;
	while (*(s + i))
	{
		// if (*(s + i) == '"')
		// {
		// 	if (quote)
		// 	{
		// 		c = ' ';			
		// 	}
		// 	else
		// 	{
		// 		c = '"';
		// 	}
		// }
		if (*(s + i) == '"')
			quote = true;
		else if (*(s + i) == '"')
			quote = false;
		if (!has_delimiter_first(*(s + i)) && !quote)
		{
			j = count_length_first(s, c, &i, &first);
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

char	**ft_split_first(char const *s, char c)
{
	char			**split;

	split = (char **) malloc (sizeof(char *) * (2 + 1));
	if (split == 0)
		return (0);
	split_arr_first(split, s, c);
	return (split);
}

// int	main(void)
// {
// 	char *s = "echo \"test | abcd\"";
// 	char **split = ft_split_first(s, ' ');
// 	printf("%s\n", split[0]);
// }