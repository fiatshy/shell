/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:15:09 by sunghyki          #+#    #+#             */
/*   Updated: 2024/02/26 17:15:58 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*map_arr;

	i = 0;
	len = ft_strlen(s);
	map_arr = (char *) malloc (sizeof(char) * (len + 1));
	if (map_arr == 0)
		return (0);
	while (*(s + i))
	{
		map_arr[i] = f(i, *(s + i));
		i++;
	}
	map_arr[i] = '\0';
	return (map_arr);
}
