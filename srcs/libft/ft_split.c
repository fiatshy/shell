/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:00:17 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:18:23 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline char	**wordfree(char **s, int i)
{
	while (--i >= 0 && s[i])
		ft_free((void **)(&(s[i])));
	ft_free((void **)(&s));
	return (NULL);
}

char	**ft_split(const char *s, bool (*cmp)(int))
{
	int		i;
	char	*from;
	char	**buf;

	i = 0;
	if (!s || !ft_calloc((void **)(&buf), ft_wordlen(s, cmp) + 1,
		sizeof(char *)))
		return (NULL);
	while (*s)
	{
		if (!cmp(*s))
		{
			from = (char *)s;
			while (*s && !cmp(*s))
				++s;
			buf[i] = ft_substr(from, 0, (s - from));
			if (!buf[i++])
				return (wordfree(buf, i));
		}
		else
			++s;
	}
	buf[i] = NULL;
	return (buf);
}
