/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:00:47 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:00:48 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	src;
	size_t	dst;

	src = ft_strlen(s);
	dst = len;
	if (dst > src)
		dst = src;
	if (!s || !ft_calloc((void **)(&buf), dst + 1, sizeof(char)))
		return (NULL);
	if ((size_t)start < src)
		ft_strlcpy(buf, s + start, dst + 1);
	return (buf);
}
