/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:34:27 by sunghyki          #+#    #+#             */
/*   Updated: 2024/03/06 17:33:14 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	convert(char *str, long div)
{
	if ('0' > *str || *str > '9')
		return (0);
	return (((*str - '0') * div) + convert(str + 1, div / 10));
}

static long	make_div(char *str)
{
	long	j;
	long	div;

	j = 0;
	div = 1;
	while (*(str + j + 1))
	{
		if ('0' > *(str + j + 1) || *(str + j + 1) > '9')
			return (div);
		div = div * 10;
		j++;
	}
	return (div);
}

int	ft_atoi(const char *str)
{
	long	sign;

	while ((9 <= (int)*str && (int)*str <= 13) || (int)*str == 32)
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	if (*str == 0)
		return (0);
	return ((int)(sign * convert((char *)str, make_div((char *)str))));
}
