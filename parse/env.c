/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:10 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:11 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_test.h"

char	*get_env(void)
{
	int		fd;
	char	*temp;
	char	**split;

	fd = open("environment", O_RDONLY);
	temp = get_next_line(fd);
	while (temp)
	{
		if (ft_strncmp(temp, "PATH", 4) == 0)
		{
			split = ft_split(temp, '=');
			free(temp);
			return (split[1]);
		}
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	close(fd);
	return (NULL);
}

char	*get_envv(t_cmd_struct *tcst)
{
	t_list	*temp;
	char	**temp_split;

	temp = *tcst->lst_env;
	while (temp)
	{
		if (ft_strncmp(temp->content, "PATH", 4) == 0)
		{
			temp_split = ft_split(temp->content, '=');
			return (temp_split[1]);
		}
		temp = temp->next;
	}
	return (NULL);
}
