/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 05:00:44 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 05:00:44 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtrim(char **s)
{
	size_t	len;

	while (ft_isspace(**s))
		++(*s);
	len = ft_strlen(*s);
	while (ft_isspace((*s)[len - 1]))
		--len;
	(*s)[len] = '\0';
}
