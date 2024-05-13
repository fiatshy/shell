/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:00:20 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:00:21 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strappend(char **s, char *s2)
{
	char	*s1;

	if (!*s)
	{
		*s = ft_strdup(s2);
		if (!*s)
			return (false);
		return (true);
	}
	s1 = ft_strdup(*s);
	ft_free((void **)s);
	if (!s1)
		return (false);
	if (!ft_calloc((void **)s, ft_strlen(s1) + ft_strlen(s2) + 1, 1))
	{
		ft_free((void **)(&s1));
		return (false);
	}
	ft_strlcpy(*s, s1, ft_strlen(s1) + 1);
	ft_strlcpy(*s + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	ft_free((void **)(&s1));
	return (true);
}
