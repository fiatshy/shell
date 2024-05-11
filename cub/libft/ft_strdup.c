/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:03:24 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 12:03:26 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup_ptr;

	dup_ptr = (char *) malloc (sizeof(char) * (ft_strlen(s) + 1));
	if (dup_ptr == 0)
		return (0);
	i = 0;
	while (i < ft_strlen(s) && s[i])
	{
		dup_ptr[i] = s[i];
		i++;
	}
	dup_ptr[i] = '\0';
	return (dup_ptr);
}
