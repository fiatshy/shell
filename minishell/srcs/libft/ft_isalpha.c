/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:07:48 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/22 16:14:55 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_islower(unsigned int c)
{
	if ('a' <= c && c <= 'z')
		return (1);
	return (0);
}

static int	ft_isupper(unsigned int c)
{
	if ('A' <= c && c <= 'Z')
		return (c);
	return (0);
}

int	ft_isalpha(int c)
{
	if (ft_islower(c) || ft_isupper(c))
		return (c);
	return (0);
}
