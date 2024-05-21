/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:15:27 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 17:15:44 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*join_str;

	join_str = (char *) malloc \
		(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join_str == 0)
		return (0);
	i = 0;
	while (*(s1 + i))
	{
		join_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (*(s2 + j))
	{
		join_str[i] = s2[j];
		i++;
		j++;
	}
	join_str[i] = '\0';
	return (join_str);
}
