/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:09:57 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 12:02:02 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy_overlap(void *dst, const void *src, size_t len)
{
	while (len >= 1)
	{
		*(char *)(dst + len - 1) = *(char *)(src + len - 1);
		len--;
	}
}

static void	ft_copy(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (0);
	if (dst > src)
		ft_copy_overlap(dst, src, len);
	else if (dst < src)
		ft_copy(dst, src, len);
	else
		ft_copy(dst, src, len);
	return (dst);
}
