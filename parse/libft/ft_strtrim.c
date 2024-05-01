/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:16:25 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 17:16:26 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*cpy;

	i = 0;
	j = ft_strlen(s1);
	while (is_set(*(s1 + i), set))
		i++;
	if (i == ft_strlen(s1))
	{
		cpy = (char *) malloc (1);
		cpy[0] = 0;
		return (cpy);
	}
	while (is_set(*(s1 + j - 1), set))
		j--;
	cpy = (char *) malloc (sizeof(char) * (j - i + 1));
	if (cpy == 0)
		return (0);
	ft_memmove(cpy, s1 + i, j - i);
	cpy[j - i] = 0;
	return (cpy);
}
