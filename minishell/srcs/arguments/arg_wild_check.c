/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_wild_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:23 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:24 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_asterisk(char *s)
{
	while (*s)
	{
		if (*s == ' ')
		{
			while (*s == ' ')
			{
				s++;
			}
			break ;
		}
		s++;
	}
	while (*s)
	{
		if (*s == '*')
			return (1);
		s++;
	}
	return (0);
}

int	process_wildcard(char *f, char *t)
{
	while (*t)
	{
		if (*t == '*')
		{
			t++;
			while (*f)
			{
				if (*f == *t)
					break ;
				f++;
			}
		}
		else
		{
			if (*f == *t)
			{
				f++;
				t++;
			}
			else if (*f != *t)
				return (0);
		}
	}
	return (1);
}

int	how_much_files(char	*target)
{
	DIR				*dp;
	struct dirent	*entry;
	char			buf[255];
	int				count;

	count = 0;
	ft_memset(buf, 0, 255);
	getcwd(buf, 255);
	dp = opendir(buf);
	entry = readdir(dp);
	while (entry)
	{
		if (process_wildcard(entry->d_name, target))
			count++;
		entry = readdir(dp);
	}
	closedir(dp);
	return (count);
}
