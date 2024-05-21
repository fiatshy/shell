/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:03:49 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 10:44:25 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = 0;
	while (*(s + i))
	{
		if (*(s + i) == (unsigned char)c)
			ptr = (char *)(s + i);
		i++;
	}
	if ((unsigned char)c == *(s + i))
		return ((char *)(s + i));
	return (ptr);
}
