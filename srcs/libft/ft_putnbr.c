/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:00:11 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:00:12 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putnbr(n / 10, fd);
		ft_putchar(8 + '0', fd);
	}
	else if (n < 0)
	{
		ft_putchar('-', fd);
		ft_putnbr(-n, fd);
	}
	else
	{
		if (n > 9)
			ft_putnbr(n / 10, fd);
		ft_putchar(n % 10 + '0', fd);
	}
}
