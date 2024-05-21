/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:08:17 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 12:02:51 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	search(const char *haystack, \
	const char *needle, size_t i, size_t len)
{
	size_t	j;
	size_t	flag;

	j = 0;
	flag = 1;
	while (*(needle + j))
	{
		if ((i + j) >= len)
		{
			flag = 0;
			return (flag);
		}
		if (*(haystack + i + j) != *(needle + j))
		{
			flag = 0;
			return (flag);
		}
		j++;
	}
	return (flag);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	flag;

	if (!*needle)
		return ((char *)(haystack));
	i = 0;
	flag = 0;
	while (i < len && *(haystack + i))
	{
		if (*(haystack + i) == *needle)
		{
			flag = search(haystack, needle, i, len);
			if (flag)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (0);
}
