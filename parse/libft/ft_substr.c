/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:16:40 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 17:16:41 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	cmp_len;
	char	*subptr;

	i = 0;
	if (s == 0)
		return (0);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	cmp_len = ft_strlen(s + start);
	if (cmp_len < len)
		len = cmp_len;
	subptr = (char *)malloc(sizeof(char) * (len + 1));
	if (subptr == 0)
		return (0);
	while (i < len && s[start])
	{
		subptr[i] = s[start];
		i++;
		start++;
	}
	subptr[i] = '\0';
	return (subptr);
}
