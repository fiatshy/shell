/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:13:57 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 17:19:34 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	i;
	char			*s;

	i = 0;
	s = ft_itoa(n);
	while (*(s + i))
	{
		write(fd, s + i, sizeof(char));
		i++;
	}
	free(s);
}
