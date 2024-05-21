/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:47 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:48 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_slash_reverse(char *s, int target)
{
	int	len;
	int	count;

	count = 0;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (*(s + len) == '/')
			count++;
		if (count == target)
			return (len);
		len--;
	}
	return (0);
}

void	copy_path(char temp[255], char *src)
{
	int	i;

	while (temp[i])
		i++;
	temp[i] = '/';
	i++;
	while (*src)
	{
		temp[i] = *src;
		i++;
		src++;
	}
}

int	has_relative_path(char *s)
{
	while (1)
	{
		if (ft_strncmp(s, "..", 2) == 0)
			return (1);
		s++;
		if (*s == 0)
			break ;
	}
	return (0);
}

int	has_multi_dots(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '/')
			count = 0;
		else if (*s == '.')
			count++;
		s++;
		if (count > 2)
			return (-1);
	}
	return (0);
}
