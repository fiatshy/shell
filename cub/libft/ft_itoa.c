/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:11:33 by sunghyki          #+#    #+#             */
/*   Updated: 2024/03/03 11:54:47 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_pos(int n)
{
	unsigned int	i;

	i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int	get_divd(int pos)
{
	int	i;
	int	divd;

	i = 0;
	divd = 1;
	while (i < (pos - 1))
	{
		divd *= 10;
		i++;
	}
	return (divd);
}

static void	set_minus(int *minus, int n)
{
	*minus = 0;
	if (n < 0)
		*minus = 1;
}

static char	*get_char(int pos, int divd, int n)
{
	int		i;
	int		q;
	char	*n_str;
	int		minus;

	i = 0;
	set_minus(&minus, n);
	n_str = (char *) malloc (sizeof(char) * (pos + 1 + minus));
	if (n_str == 0)
		return (0);
	if (n < 0)
		n_str[i++] = '-';
	if (n > 0)
		n *= -1;
	while (i < (pos + minus))
	{
		q = (n / divd) * -1;
		n_str[i] = q + '0';
		n = (n + (q * divd));
		divd /= 10;
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}

char	*ft_itoa(int n)
{
	int		pos;
	char	*n_str;

	if (n == 0)
	{
		n_str = (char *) malloc (sizeof(char) * 2);
		n_str[0] = '0';
		n_str[1] = 0;
		return (n_str);
	}
	pos = get_pos(n);
	n_str = get_char(pos, get_divd(pos), n);
	return (n_str);
}
