/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_wild_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:26 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:31 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

void	opendir_args(DIR **dp, struct dirent **entry)
{
	char	buf[255];

	ft_memset(buf, 0, 255);
	getcwd(buf, 255);
	*dp = opendir(buf);
	*entry = readdir(*dp);
}

char	**split_args(char *s, int length)
{
	DIR				*dp;
	struct dirent	*entry;
	char			buf[255];
	char			**ret;
	int				i;

	ret = malloc (sizeof(char *) * (length + 1));
	opendir_args(&dp, &entry);
	i = 1;
	while (entry)
	{
		if (process_wildcard(entry->d_name, s))
		{
			ret[i] = malloc (ft_strlen(entry->d_name));
			ft_memcpy(ret[i], entry->d_name, ft_strlen(entry->d_name));
			ret[i][ft_strlen(entry->d_name)] = 0;
			i++;
		}
		entry = readdir(dp);
	}
	ret[i] = 0;
	closedir(dp);
	return (ret);
}

char	**split_asterisk(char *s)
{
	char	**ret;
	char	**temp;
	int		length;

	temp = ft_split(s, ' ');
	length = how_much_files(temp[1]);
	ret = split_args(temp[1], length + 1);
	ret[0] = malloc (sizeof(ft_strlen(temp[0]) + 1));
	ft_memcpy(ret[0], temp[0], ft_strlen(temp[0]));
	ret[0][ft_strlen(temp[0])] = 0;
	free(temp[0]);
	free(temp[1]);
	free(temp);
	return (ret);
}
