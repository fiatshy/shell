/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:58:48 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 04:58:48 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (ft_isspace(*s))
		++s;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	while (ft_isdigit(*s))
	{
		if ((res >= 0) != ((res << 1) >= 0) || (res >= 0) != ((res << 2) >= 0)
			|| (res >= 0) != ((res << 3) >= 0) || (res >= 0) != (res * 10 + (*s
					- '0') >= 0))
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		res = res * 10 + (*s++ - '0');
	}
	return (res * sign);
}
