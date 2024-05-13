/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:59:26 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 04:59:26 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		neg;
	int		i;
	int		cnt;
	char	*buf;

	neg = 0;
	i = -1;
	if (n < 0)
		++neg;
	if (neg)
		++i;
	cnt = (int)ft_numlen(n);
	if (!ft_calloc((void **)(&buf), cnt + 1, sizeof(char)))
		return (NULL);
	if (neg)
		buf[0] = '-';
	while (++i < cnt)
	{
		buf[cnt - (!neg) - i] = "0123456789"[ft_abs(n % 10)];
		n /= 10;
	}
	buf[cnt] = '\0';
	return (buf);
}
