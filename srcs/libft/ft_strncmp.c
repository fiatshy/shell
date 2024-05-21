/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:05:35 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 11:09:54 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while ((*(s1 + i) || *(s2 + i)) && i < n)
	{
		diff = *(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i);
		if (diff != 0)
			return (diff);
		i++;
	}
	return (0);
}
