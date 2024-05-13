/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:00:56 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:00:56 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordlen(const char *s, bool (*cmp)(int))
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (!cmp(*s))
		{
			++cnt;
			while (*s && !cmp(*s))
				++s;
		}
		else
			++s;
	}
	return (cnt);
}
