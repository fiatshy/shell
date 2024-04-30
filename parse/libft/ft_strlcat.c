/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:29:27 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 10:41:51 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;

	if (!dst && !size)
		return (0);
	dst_len = ft_strlen(dst);
	if (size < dst_len)
	{
		return (ft_strlen(src) + size);
	}
	i = 0;
	while (*(src + i) && (size > (dst_len + i) + 1))
	{
		*(dst + dst_len + i) = *(src + i);
		i++;
	}
	*(dst + dst_len + i) = '\0';
	return (dst_len + ft_strlen(src));
}
