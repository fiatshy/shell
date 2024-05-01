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

size_t	count_words(char const *s, char c)
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

char	**split_arr(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	idx;
	bool quote;

	i = 0;
	idx = 0;
	quote = false;
	while (*(s + i))
	{
		if (*(s + i) == '"')
		{
			if (quote)
			{
				c = ' ';			
			}
			else
			{
				c = '"';
			}
		}
		if (*(s + i) != c)
		{
			j = count_length(s, c, &i);
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

// int	main(void)
// {
// 	char *s = "car \"ls -la\" hello";
// 	char **split = ft_split(s, ' ');
// 	printf("%s %s %s\n", split[0], split[1], split[2]);
// }
