/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:00:08 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:00:09 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr(s, fd);
	ft_putchar('\n', fd);
}
