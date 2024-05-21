/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:36:39 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/17 14:36:41 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*what_quotes(char *s)
{
	while (*s)
	{
		if (*s == '\"')
			return ("\"");
		else if (*s == '\'')
			return ("\'");
		s++;
	}
	return (NULL);
}

void	trim(t_cmd_struct *tcst, int index, int i)
{
	char	*delim;

	delim = what_quotes(tcst->tcmd[index]->arg[i]);
	if (delim == NULL)
	{
		if (tcst->tcmd[index]->arg[i][0] == '?')
			printf("%d ", tcst->status);
		else
			printf("%s ", tcst->tcmd[index]->arg[i]);
	}
	else
	{
		if (tcst->tcmd[index]->arg[i][0] == '?')
			printf("%d ", tcst->status);
		else
			printf("%s ", tcst->tcmd[index]->arg[i]);
	}
}

void	get_file_length(int *i)
{
	int		fd;
	char	*temp;

	fd = open("environment", O_RDWR, 0777);
	*i = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		(*i)++;
		temp = get_next_line(fd);
		free(temp);
	}
	free(temp);
	close(fd);
}

void	write_env(char **arr, t_cmd_struct *tcst, int index)
{
	int		fd;
	int		i;
	char	**temp_split;

	remove("environment");
	fd = open("environment", O_CREAT | O_WRONLY, 0777);
	i = 0;
	while (arr[i])
	{
		temp_split = ft_split(arr[i], '=');
		if (ft_strncmp(temp_split[0], tcst->tcmd[index]->arg[1], \
			ft_strlen(temp_split[0])) != 0)
			write(fd, arr[i], ft_strlen(arr[i]));
		free(temp_split[0]);
		free(temp_split[1]);
		free(temp_split);
		i++;
	}
	close(fd);
}

int	is_empty_string(char *s)
{
	int	flag;

	flag = 1;
	s = ft_strtrim(s, "'\"");
	while (*s)
	{
		if ((9 > *s || *s > 13) && (*s != 32))
			flag = 0;
		s++;
	}
	return (flag);
}
